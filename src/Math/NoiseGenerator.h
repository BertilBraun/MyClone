#pragma once
struct NoiseParameters
{
	int octaves;
	int amplitude;
	int smoothness;
	int heightOffset;

	double roughness;
};

class NoiseGenerator {
public:
	NoiseGenerator(int seed);

	double getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;
	double getValue(int x, int y, int z, int chunkX, int chunkZ) const noexcept;

	void setParameters(const NoiseParameters& params) noexcept;
	void setSeed(int seed);

private:	
	double getNoise(int n) const noexcept;
	double getNoise(double x, double z) const noexcept;
	double getNoise(double x, double y, double z) const noexcept;

	double lerp(double a, double b, double z) const noexcept;

	double noise(double  x, double  z) const noexcept;
	double noise(double  x, double y, double  z) const noexcept;
	
	NoiseParameters m_noiseParameters;

	int m_seed;
};

