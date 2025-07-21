#pragma once

template<class ... T>
class ResourceCache
{
public:
	static ResourceCache& Get()
	{
		if (!mCache)
		{
			mCache = new ResourceCache();
		}

		return *mCache;
	}


	template<class U, class ... Args>
	U& Insert(const std::string& handle, Args && ... args)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(mResourceCache);

		if (map.contains(handle))
		{
			throw new std::runtime_error("Resource pool already contains resource called " + handle);
		}

		const auto [iter, inserted] = map.emplace(std::make_pair(handle, U{ std::forward<Args>(args) ... }));

		return iter->second;
	}


	template<class U>
	U& Find(const std::string& handle)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(mResourceCache);

		if (!map.contains(handle))
		{
			throw new std::runtime_error("Resource pool does not contain resource called " + handle);
		}

		const auto object = map.find(handle);

		return object->second;
	}

	template<class U>
	void Erase(const std::string& handle)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(mResourceCache);

		if (!map.contains(handle))
		{
			throw new std::runtime_error("Resource pool does not contain resource called " + handle);
		}

		map.erase(handle);

	}

	template<class U>
	std::unordered_map<std::string, U>& FindEntireMap()
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(mResourceCache);
		return map;
	}

	void Free()
	{
		std::apply([](auto&... map) {(map.clear(), ...); }, mResourceCache);
		delete mCache;
	}


private:
	std::tuple<std::unordered_map<std::string, T> ... > mResourceCache;

	inline static ResourceCache* mCache = nullptr;
};