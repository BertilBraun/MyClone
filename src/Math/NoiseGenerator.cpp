#include "NoiseGenerator.h"

#include "defines.h"
#include "Vector2.h"
#include "Utils/UtilityFunctions.h"
#include <cmath>

NoiseGenerator::NoiseGenerator(int seed)
:   m_seed  (seed)
{
	m_noiseParameters.octaves       = 7;
	m_noiseParameters.amplitude     = 70;
	m_noiseParameters.smoothness    = 235;
	m_noiseParameters.heightOffset  = -5;
	m_noiseParameters.roughness     = 0.53;
}

void NoiseGenerator::setParameters(const NoiseParameters& params) noexcept
{
	m_noiseParameters = params;
}

void NoiseGenerator::setSeed(int seed) {
	m_seed = seed;
}

double NoiseGenerator::getNoise(int  n) const noexcept
{
	n += m_seed;
	n = (n << 13) ^ n;
	auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

	return 1.0 - ((double)newN / 1073741824.0);
}

double NoiseGenerator::getNoise(double  x, double  z) const noexcept
{
	return getNoise((int)(x + z * 57));
}

double NoiseGenerator::getNoise(double x, double y, double z) const noexcept
{
	return getNoise((int)(x + y * 5700 + z * 57));
}

double NoiseGenerator::lerp(double a, double b, double z) const noexcept
{
	double mu2 = (1 - std::cos(z * 3.14)) / 2;
	return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::noise(double  x, double  z) const noexcept
{
	auto floorX = (double)((int)x); 
	auto floorZ = (double)((int)z);

	auto    s = 0.0,
			t = 0.0,
			u = 0.0,
			v = 0.0;

	s = getNoise(floorX,      floorZ);
	t = getNoise(floorX + 1,  floorZ);
	u = getNoise(floorX,      floorZ + 1);
	v = getNoise(floorX + 1,  floorZ + 1);

	//Interpolate between the values.
	auto rec1 = lerp(s, t, x - floorX);
	auto rec2 = lerp(u, v, x - floorX);
	auto rec3 = lerp(rec1, rec2, z - floorZ);
	return rec3;
}

double NoiseGenerator::noise(double x, double y, double z) const noexcept
{
	auto floorX = (double)((int)x);
	auto floorY = (double)((int)y);
	auto floorZ = (double)((int)z);

	auto r = 0.0,
		 s = 0.0,
		 t = 0.0,
		 u = 0.0,
		 v = 0.0,
		 w = 0.0;

	r = getNoise(floorX, floorZ);
	s = getNoise(floorX + 1, floorZ);
	t = getNoise(floorX, floorZ + 1);
	u = getNoise(floorX + 1, floorZ + 1);
	v = getNoise(floorX + 1, floorZ + 1);
	w = getNoise(floorX + 1, floorZ + 1);

	//Interpolate between the values.
	auto rec1 = lerp(s, t, x - floorX);
	auto rec2 = lerp(u, v, x - floorX);
	auto rec3 = lerp(rec1, rec2, z - floorZ);
	return rec3;
}

double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ) const noexcept
{
	double newX = x + (chunkX * CHUNK_SIZE),
		   newZ = z + (chunkZ * CHUNK_SIZE);

	if (newX < 0 || newZ < 0)
		return WATERLEVEL;

	double totalValue = 0.0;

	for (auto a = 0; a < m_noiseParameters.octaves - 1; a++)
	{
		double frequency = pow(2.0, a);

		totalValue += noise(newX * frequency / m_noiseParameters.smoothness,
							newZ * frequency / m_noiseParameters.smoothness)
							* pow(m_noiseParameters.roughness, a);
	}

	auto val = (((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) + m_noiseParameters.heightOffset;

	return val > 0 ? val : 1;
}

double NoiseGenerator::getValue(int x, int y, int z, int chunkX, int chunkZ) const noexcept {

	return getNoise(x, y, z);
}


