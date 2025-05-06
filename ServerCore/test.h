#pragma once

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(xAlloc(sizeof(Type)));

	//placement new
	new(memory)Type(std::forward<Args>(args)...);

	return memory;
}