#pragma once


class openglTexture
{
public:
	openglTexture() = default;
	openglTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip = false);
	openglTexture(const std::filesystem::path& directory, const std::filesystem::path& path, aiTextureType type);

	void Attach() const;

	void Load(const std::filesystem::path& path, bool flip = false);

	uint32_t GetHandle() const { return mHandle; }

	std::string& GetName() { return mSamplerName; }

	std::filesystem::path& GetPath() { return mPath; }
	std::filesystem::path& GetDirectory() { return mDir; }

	aiTextureType GetType() { return mType; }

private:
	aiTextureType mType;

	std::filesystem::path mPath;
	std::filesystem::path mDir;

private:
	uint32_t mHandle = 0;

	std::string mSamplerName = "";

	int mWidth;
	int mHeight;
	int mChannels;
};

