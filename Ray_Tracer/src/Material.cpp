#include "Material.h"
#include <math.h>       /* pow */

Vector3f Material::shade(const Ray &ray,
    const Hit &hit,
    const Vector3f &dirToLight,
    const Vector3f &lightIntensity)
{
    // Diffuse shading + specular shading
    Vector3f L = dirToLight.normalized();
    Vector3f N = hit.getNormal().normalized();
    Vector3f R = (ray.getDirection() + 2 * Vector3f::dot(-ray.getDirection(), N) * N);
    float diffuseClamp = fmax(0, Vector3f::dot(L, N));
    float specularClamp = pow(fmax(0, Vector3f::dot(L, R)), _shininess);
    
    Vector3f diffuseShading = _diffuseColor * diffuseClamp * lightIntensity;
    Vector3f specularShading = _specularColor * specularClamp * lightIntensity;

    return diffuseShading + specularShading;
    
}
