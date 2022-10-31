#pragma once
#include <Config.h>
#include "Core/Log.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <Graphics/Vertex.h>
#include <string>
#include <fstream>
#include <array>
#include <sstream>
#include <chrono>
#include <filesystem>

#define BUF_SIZE (8 * 1024)

SOLAR_BEGIN
struct ObjMesh
{
    std::string                     name;
    std::vector<glm::vec3>          positions;
    std::vector<glm::vec2>          texCoords;
    std::vector<glm::vec3>          normals;
    std::vector<std::uint32_t>      positions_indices;
    std::vector<std::uint32_t>      uv_indices;
    std::vector<std::uint32_t>      nrn_indices;

    bool IsEmpty() const
    {
        return name.empty() && positions_indices.empty() && uv_indices.empty() && nrn_indices.empty();
    }
};


static void LoadObj(const std::filesystem::path& filepath, std::vector<ObjMesh>& OutObjMeshes)
{
    SOLAR_LOG_TRACE("[ObjParser] Read Obj file '{}'", filepath.string());
    auto chrono_start = std::chrono::high_resolution_clock::now();
    std::ifstream stream(filepath.string(), std::ios::in);
    if(!stream.is_open())
        SOLAR_LOG_ERROR("[ObjParser] Failed to open file: {}", filepath.string());
    
    
    std::stringstream buffer;
    buffer << stream.rdbuf();
    
    OutObjMeshes.clear();
    std::string line;
    ObjMesh objMesh{};
    
    while(std::getline(buffer, line))
    {
        if(line[0] == '#') continue;

        if(line[0] == 'o')
        {
            if(objMesh.IsEmpty())
            {
                objMesh.name = line.substr(2, line.size());
            } else
            {
                OutObjMeshes.push_back(objMesh);
                objMesh = {};
                objMesh.name = line.substr(2, line.size());
            }
        }

        if(line[0] == 'v' && line[1] == ' ')
        {
            glm::vec3 v;
            sscanf(line.c_str(), "v %f %f %f", &v[0], &v[1], &v[2]);
            objMesh.positions.push_back(v);
            continue;
        }

        if(line[0] == 'v' && line[1] == 'n')
        {
            glm::vec3 vn;
            sscanf(line.c_str(), "vn %f %f %f", &vn[0], &vn[1], &vn[2]);
            objMesh.normals.push_back(vn);
            continue;
        }

        if(line[0] == 'v' && line[1] == 't')
        {
            glm::vec2 vt;
            sscanf(line.c_str(), "vt %f %f", &vt[0], &vt[1]);
            objMesh.texCoords.push_back(vt);
            continue;
        }

        if(line[0] == 'f')
        {
            std::array<std::uint32_t, 3> pos{};
            std::array<std::uint32_t, 3> uv{};
            std::array<std::uint32_t, 3> nrm{};
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &pos[0], &uv[0], &nrm[0],
                &pos[1], &uv[1], &nrm[1],
                &pos[2], &uv[2], &nrm[2]);
                    
            objMesh.positions_indices.push_back(pos[0]);
            objMesh.positions_indices.push_back(pos[1]);
            objMesh.positions_indices.push_back(pos[2]);

            objMesh.uv_indices.push_back(uv[0]);
            objMesh.uv_indices.push_back(uv[1]);
            objMesh.uv_indices.push_back(uv[2]);

            objMesh.nrn_indices.push_back(nrm[0]);
            objMesh.nrn_indices.push_back(nrm[1]);
            objMesh.nrn_indices.push_back(nrm[2]);
        }
    }

    if(!objMesh.IsEmpty())
    {
        OutObjMeshes.push_back(objMesh);
    }

    auto chrono_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(chrono_end - chrono_start);
    
    for(const auto& mesh : OutObjMeshes)
    {
        SOLAR_LOG_TRACE("");
        SOLAR_LOG_TRACE("Mesh '{}'", mesh.name);
        SOLAR_LOG_TRACE("Positions: {}", mesh.positions.size());
        SOLAR_LOG_TRACE("Texture Coordinates: {}", mesh.texCoords.size());
        SOLAR_LOG_TRACE("Normals: {}", mesh.normals.size());
        SOLAR_LOG_TRACE("Faces: {}", mesh.positions_indices.size());
    }
    SOLAR_LOG_INFO("[ObjParser] Reading took: {} seconds.", ((double)duration.count() / 1e6));
}

static void ConvertObjMesh(const std::vector<ObjMesh>& ObjMeshes, std::vector<Vertex>& OutVertices)
{
    OutVertices.clear();
    for(std::size_t i = 0; i < ObjMeshes.size(); i++)
    {
        for(std::size_t j = 0; j < ObjMeshes[i].positions_indices.size(); j++)
        {
            OutVertices.push_back({
                ObjMeshes[i].positions[ObjMeshes[i].positions_indices[i] - 1 - (i * ObjMeshes[i].positions.size())],
                ObjMeshes[i].texCoords[ObjMeshes[i].uv_indices[i] - 1 - (i * ObjMeshes[i].texCoords.size())],
                ObjMeshes[i].normals[ObjMeshes[i].nrn_indices[i] - 1 - (i * ObjMeshes[i].normals.size())],
                {0.0f, 0.0f, 0.0f, 0.0f }
            });
        }
    }
}

SOLAR_END