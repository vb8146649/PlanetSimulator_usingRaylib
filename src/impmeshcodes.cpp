#include "impmeshcodes.h"

ImpMeshC::ImpMeshC()
{
}


void ImpMeshC::AdjustUVCoordinates(Mesh &mesh, float xOffset, float yOffset)
{
    float *texcoords = (float *)mesh.texcoords;

    for (int i = 0; i < mesh.vertexCount; i++)
    {
        texcoords[i * 2] += xOffset - (int)xOffset; 
        texcoords[i * 2 + 1] += yOffset;            
    }

    UploadMesh(&mesh, true);
}

void ImpMeshC::AdjustTextureCoordinates(Mesh &mesh)
{
    float *texcoords = (float *)mesh.texcoords;

    for (int i = 0; i < mesh.vertexCount; i++)
    {
        Vector3 position = ((Vector3 *)mesh.vertices)[i];
        position = Vector3Normalize(position);
        // Calculate spherical coordinates (latitude and longitude)
        float u = 0.5f + atan2(position.z, position.x) / (2.0f * PI);
        float v = 0.5f - asin(position.y) / PI;

        // Apply texture coordinates (adjust for specific texture alignment issues)
        texcoords[i * 2] = u;
        texcoords[i * 2 + 1] = v;
    }

    // Upload the modified mesh data
    UploadMesh(&mesh, true);
}


void ImpMeshC::RotateTextureCoordinates90(Mesh &mesh)
{
    float *texcoords = (float *)mesh.texcoords;

    // Rotate U and V coordinates for each vertex by 90 degrees
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        float u = texcoords[i * 2];     // Current U coordinate
        float v = texcoords[i * 2 + 1]; // Current V coordinate

        // Rotate 90 degrees (swap and invert U and V)
        texcoords[i * 2] = 1.0f - u; // Invert V coordinate
        texcoords[i * 2 + 1] = v;    // Set U coordinate to original V
    }

    // Upload the modified mesh data
    UploadMesh(&mesh, true);
}

void ImpMeshC::TransposeTextureCoordinates(Mesh &mesh)
{
    float *texcoords = (float *)mesh.texcoords;

    // Swap U and V coordinates for each vertex
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        float u = texcoords[i * 2];     // Current U coordinate
        float v = texcoords[i * 2 + 1]; // Current V coordinate

        // Transpose (swap) U and V
        texcoords[i * 2] = v;
        texcoords[i * 2 + 1] = u;
    }

    // Upload the modified mesh data
    UploadMesh(&mesh, true);
}

Vector3 ImpMeshC::RotateX(Vector3 v, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        v.x,
        c * v.y - s * v.z,
        s * v.y + c * v.z};
}

// Function to rotate a vector around the y-axis
Vector3 ImpMeshC::RotateY(Vector3 v, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        c * v.x + s * v.z,
        v.y,
        -s * v.x + c * v.z};
}

// Function to rotate a vector around the z-axis
Vector3 ImpMeshC::RotateZ(Vector3 v, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        c * v.x - s * v.y,
        s * v.x + c * v.y,
        v.z};
}