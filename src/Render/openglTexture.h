#pragma once


class openglTexture
{
public:
	openglTexture() = default;
	openglTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip = false);

	void Attach() const;

	uint32_t GetHandle() const { return mHandle; }

	std::string& GetName() { return mSamplerName; }

private:
	uint32_t mHandle = 0;

	std::string mSamplerName = "";

	int mWidth;
	int mHeight;
	int mChannels;
};

