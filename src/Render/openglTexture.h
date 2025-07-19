#pragma once


class openglTexture
{
public:
	openglTexture() = default;
	openglTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip = false);

	void Attach();

	inline uint32_t const GetHandle() { return mHandle; }

	inline const std::string& const GetName() const { return mSamplerName; }

private:
	uint32_t mHandle;

	std::string mSamplerName = "";

	int mWidth;
	int mHeight;
	int mChannels;
};

