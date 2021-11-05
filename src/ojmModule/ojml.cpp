
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include "ojmModule/ojml.hpp"
#include "tools/context.hpp"
#include "EntityCore/Core/BufferMgr.hpp"
#include "EntityCore/Resource/VertexArray.hpp"
#include "EntityCore/Resource/VertexBuffer.hpp"
#include "EntityCore/Resource/TransferMgr.hpp"
#include "EntityCore/Resource/Pipeline.hpp"

// *****************************************************************************
//
// CLASSE OJML: un dérivé de OJM mais avec un seul shape
//
// *****************************************************************************

OjmL::OjmL(const std::string & _fileName)
{
	is_ok = false;
	is_ok = init(_fileName);
}

OjmL::~OjmL()
{
	if (index.buffer) {
		Context::instance->indexBufferMgr->releaseBuffer(index);
	}
}

bool OjmL::init(const std::string & _fileName)
{
	pIndex = (unsigned int *) Context::instance->transfer->beginPlanCopy(0); // We don't know the size yet
	is_ok = readOJML(_fileName);
	if (is_ok) {
		initGLparam();
	} else {
		Context::instance->transfer->endPlanCopy(index, 0);
	}
	return is_ok;
}

void OjmL::bind(VkCommandBuffer &cmd)
{
	if (is_ok) {
		vkCmdBindIndexBuffer(cmd, index.buffer, 0, VK_INDEX_TYPE_UINT32);
		VertexArray::bindGlobal(cmd, vertex->get());
	}
}

void OjmL::bind(Pipeline &pipeline)
{
	if (is_ok)
		pipeline.bindVertex(*Context::instance->ojmVertexArray);
}

void OjmL::draw(VkCommandBuffer &cmd)
{
	if (is_ok) {
		vkCmdDrawIndexed(cmd, indexCount, 1, index.offset / sizeof(unsigned int), vertex->getOffset(), 0);
	}
}

void OjmL::initGLparam()
{
	Context &context = *Context::instance;
	const int vertexCount = vertices.size() / 3;

	index = context.indexBufferMgr->acquireBuffer(indexCount * sizeof(int));
	context.transfer->endPlanCopy(index, indexCount * sizeof(int));
	vertex = context.ojmVertexArray->createBuffer(0, vertexCount, context.ojmBufferMgr.get());
	float *data = (float *) context.transfer->planCopy(vertex->get());
	vertex->fillEntry(3, vertexCount, vertices.data(), data);
	vertex->fillEntry(2, vertexCount, uvs.data(), data + 3);
	vertex->fillEntry(3, vertexCount, normals.data(), data + 5);
	vertices.clear();
	vertices.shrink_to_fit();
	uvs.clear();
	uvs.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
}

bool OjmL::readOJML(const std::string & _fileName)
{
    std::ifstream stream;
    char line[265];

    stream.open(_fileName.c_str(),std::ios_base::in);

    if(stream.is_open())
    {
        while(!stream.eof()) {
            stream.getline(line,256);

            switch(line[0])
            {
                case 'v':
                    {
                        Vec3f vertex;
                        std::stringstream ss(std::string(line+2));
                        ss>>vertex.v[0];
                        ss>>vertex.v[1];
                        ss>>vertex.v[2];
                        insert_vec3(vertices, vertex);
                    }
                break;
                case 'u':
                    {
                        Vec2f uv;
                        std::stringstream ss(std::string(line+2));
                        ss>>uv.v[0];
                        ss>>uv.v[1];
                        insert_vec2(uvs, uv);
                    }
                break;

                case 'n':
                    {
                        Vec3f normal;
                        std::stringstream ss(std::string(line+2));
                        ss>>normal.v[0];
                        ss>>normal.v[1];
                        ss>>normal.v[2];
                        insert_vec3(normals, normal);
                    }
                break;

                case 'j':
                    {
                        unsigned int indice[9];
                        std::stringstream ss(std::string(line+2));
                        ss>>indice[0] >> indice[1] >> indice[2] >> indice[3] >>
                            indice[4] >> indice[5] >> indice[6] >> indice[7] >>
                            indice[8];
                        for(unsigned int k=0; k<9; k++)
							*(pIndex++) = indice[k];
						indexCount += 9;
                    }
                    break;

                case 'i':
                    {
                        unsigned int indice1, indice2, indice3;
                        std::stringstream ss(std::string(line+2));
                        ss>>indice1 >> indice2 >> indice3;
                        *(pIndex++) = indice1;
                        *(pIndex++) = indice2;
                        *(pIndex++) = indice3;
						indexCount += 3;
                    }
                break;
            }
        };
        return true;
    }
	return false;
}
