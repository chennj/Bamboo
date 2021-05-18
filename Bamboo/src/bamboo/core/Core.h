#pragma once

#define OPENGL_VERSION 4.4

#include <memory>

#ifdef BB_PLATFORM_WINDOWS
	#if BB_DYNAMIC_LINK
		#ifdef BB_BUILD_DLL
			#define BAMBOO_API __declspec(dllexport) 
		#else
			#define BAMBOO_API __declspec(dllimport) 
		#endif
	#else
		#define BAMBOO_API
	#endif
#else
	#error Hello only spport Windows!
#endif

#ifdef BAMBOO_DEBUG
	#define BB_ENABLE_ASSERTS
#endif

#ifdef BB_ENABLE_ASSERTS
	#define BB_ASSERT(x, ...){if(!(x)){BB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define BB_CORE_ASSERT(x, ...){if(!(x)){BB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define BB_ASSERT(x, ...)
	#define BB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define BB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

//c++11/////////////////////////////////////////////////////////////////////////////// 
// -------------
// && ：模板参数的通用引用。
// -------------
// template<typename Ft, class... Args>
// struct call_member_function_impl<false, Ft, Args...>
// 在声明时是对类型进行展开，在调用时是对参数展开，对谁展开就放在谁后面。
// 具体看：可变参数模板：template ＜class... Args＞ 
// -------------
// class 和 typename 是一个意思。
// -------------
// std::make_shared<T>(Args&&... args)需要将参数完美转发到T对应的构造函数中。为了实现完美转发，
// std增加了forward工具函数， 完美转发主要目的一般都是为了避免拷贝，同时调用正确的函数版本。
// 为了理解完美转发，首先要理解左值与右值。
//////////////////////////////////////////////////////////////////////////////////////
namespace BAMBOO
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

