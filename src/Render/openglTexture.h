#pragma once


class openglTexture
{
public:
	openglTexture() = default;
	openglTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip = false);

	void Attach();

	uint32_t GetHandle() { return mHandle; }

	std::string& GetName() { return mSamplerName; }

private:
	uint32_t mHandle;

	std::string mSamplerName = "";

	int mWidth;
	int mHeight;
	int mChannels;
};

