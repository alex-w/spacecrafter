#include "VirtualSurface.hpp"
#include "CommandMgr.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"

static unsigned int getLayout(const BufferType& bt)
{
    switch (bt) {
        case BufferType::POS2D    : return 0;
        case BufferType::POS3D    : return 0;
        case BufferType::TEXTURE  : return 1;
        case BufferType::NORMAL   : return 2;
        case BufferType::COLOR    : return 3;
        case BufferType::COLOR4   : return 3;
        case BufferType::MAG      : return 4;
        case BufferType::SCALE    : return 5;
        default: assert(false); return 0;
    }
}

static unsigned int getDataSize(const BufferType& bt)
{
    switch (bt) {
        case BufferType::POS2D    : return 2;
        case BufferType::POS3D    : return 3;
        case BufferType::TEXTURE  : return 2;
        case BufferType::NORMAL   : return 3;
        case BufferType::COLOR    : return 3;
        case BufferType::COLOR4   : return 4;
        case BufferType::MAG      : return 1;
        case BufferType::SCALE    : return 1;
        default: assert(false); return 0;
    }
}

static VkFormat getFormat(unsigned int size)
{
    switch (size) {
        case 1: return VK_FORMAT_R32_SFLOAT;
        case 2: return VK_FORMAT_R32G32_SFLOAT;
        case 3: return VK_FORMAT_R32G32B32_SFLOAT;
        case 4: return VK_FORMAT_R32G32B32A32_SFLOAT;
        default: assert(false); return VK_FORMAT_UNDEFINED;
    }
}

VertexArray::VertexArray(VirtualSurface *_master, CommandMgr *_mgr) : master(_master), mgr(_mgr), vertexBuffer(nullptr), instanceBuffer(nullptr), indexBuffer(nullptr), vertice(offset) {}

VertexArray::~VertexArray() {}

VertexArray::VertexArray(VertexArray &model) : master(model.master), mgr(model.mgr), vertexBuffer(nullptr), instanceBuffer(nullptr), indexBuffer(nullptr), vertice(offset), bindingDesc(model.bindingDesc), bindingDesc2(model.bindingDesc2), blockSize(model.blockSize), indexBufferSize(model.indexBufferSize)
{
    // VertexArray mustn't be build for copy, at least for now
    assert(!(model.vertexBuffer || model.instanceBuffer || model.indexBuffer));
    offset = model.offset;
    attributeDesc.assign(model.attributeDesc.begin(), model.attributeDesc.end());
    attributeDesc2.assign(model.attributeDesc2.begin(), model.attributeDesc2.end());
}

void VertexArray::build(int maxVertices)
{
    vertexBuffer = std::make_unique<VertexBuffer>(master, maxVertices, bindingDesc, attributeDesc);
}

void VertexArray::buildInstanceBuffer(int maxInstances)
{
    instanceBuffer = std::make_unique<VertexBuffer>(master, maxInstances, bindingDesc2, attributeDesc2);
}

void VertexArray::bind()
{
    if (vertexUpdate) {
        vertexBuffer->update();
        vertexUpdate = false;
    }
    mgr->bindVertex(vertexBuffer.get());
    if (instanceBuffer) {
        if (instanceUpdate) {
            instanceBuffer->update();
            instanceUpdate = false;
        }
        mgr->bindVertex(vertexBuffer.get());
    }
    if (indexBuffer) {
        if (indexUpdate) {
            indexBuffer->update();
            indexUpdate = false;
        }
        mgr->bindIndex(indexBuffer.get(), VK_INDEX_TYPE_UINT32);
    }
}

void VertexArray::update()
{
    if (vertexUpdate) {
        vertexBuffer->update();
        vertexUpdate = false;
    }
    if (instanceBuffer) {
        if (instanceUpdate) {
            instanceBuffer->update();
            instanceUpdate = false;
        }
    }
    if (indexBuffer) {
        if (indexUpdate) {
            indexBuffer->update();
            indexUpdate = false;
        }
    }
}

void VertexArray::registerVertexBuffer(const BufferType& bt, const BufferAccess& ba)
{
    VkVertexInputAttributeDescription desc;
    desc.binding = 0;
    desc.location = getLayout(bt);
    desc.format = getFormat(getDataSize(bt));
    desc.offset = bindingDesc.stride;
    offset[desc.location] = blockSize;
    blockSize += getDataSize(bt);
    bindingDesc.stride = blockSize * sizeof(float);
    attributeDesc.push_back(desc);
}

void VertexArray::fillVertexBuffer(const BufferType& bt, const std::vector<float> data)
{
    fillVertexBuffer(bt, data.size(), data.data());
}

void VertexArray::fillVertexBuffer(const BufferType& bt, unsigned int size, const float* data)
{
    float *tmp = ((float *) vertexBuffer->data) + offset[getLayout(bt)];
    const uint8_t dataSize = getDataSize(bt);
    size /= dataSize;
    for (unsigned int i = 0; i < size; ++i) {
        for (uint8_t j = 0; j < dataSize; ++j)
            tmp[j] = *(data++); // *(data++); is similar to *data; data++; or data[i * dataSize + j];
        tmp += size;
    }
    vertexUpdate = true;
}

void VertexArray::registerInstanceBuffer(const BufferAccess& ba, VkFormat format, unsigned int stride)
{
    VkVertexInputAttributeDescription desc;
    desc.binding = 1;
    desc.location = attributeDesc2.size();
    desc.format = format;
    desc.offset = bindingDesc2.stride;
    blockSize += stride;
    bindingDesc2.stride = blockSize * sizeof(float);
    attributeDesc2.push_back(desc);
}

float *VertexArray::getInstanceBufferPtr()
{
    return (static_cast<float *>(instanceBuffer->data));
}

void VertexArray::registerIndexBuffer(const BufferAccess& ba, unsigned int size, size_t blockSize)
{
    indexBuffer = std::make_unique<Buffer>(master, size * blockSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
}

void VertexArray::fillIndexBuffer(const std::vector<unsigned int> data)
{
    fillIndexBuffer(data.size(), data.data());
}

void VertexArray::fillIndexBuffer(unsigned int size, const unsigned int* data)
{
    memcpy(indexBuffer->data, data, size * sizeof(unsigned int));
    indexBuffer->update();
    indexBufferSize = size;
}

void VertexArray::assumeVerticeChanged()
{
    vertexUpdate = true;
}

VertexArray::Vertice &VertexArray::operator[](int pos)
{
    vertice.setData(((float *) vertexBuffer->data) + pos * blockSize);
    return vertice;
}

VertexArray::Vertice::Vertice(std::array<uint8_t, 6> &_offset) : offset(_offset) {}

float *VertexArray::Vertice::operator[](const BufferType &bt)
{
    return data + offset[getLayout(bt)];
}
