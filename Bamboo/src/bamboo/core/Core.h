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
// && ��ģ�������ͨ�����á�
// -------------
// template<typename Ft, class... Args>
// struct call_member_function_impl<false, Ft, Args...>
// ������ʱ�Ƕ����ͽ���չ�����ڵ���ʱ�ǶԲ���չ������˭չ���ͷ���˭���档
// ���忴���ɱ����ģ�壺template ��class... Args�� 
// -------------
// class �� typename ��һ����˼��
// -------------
// std::make_shared<T>(Args&&... args)��Ҫ����������ת����T��Ӧ�Ĺ��캯���С�Ϊ��ʵ������ת����
// std������forward���ߺ����� ����ת����ҪĿ��һ�㶼��Ϊ�˱��⿽����ͬʱ������ȷ�ĺ����汾��
// Ϊ���������ת��������Ҫ�����ֵ����ֵ��
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

