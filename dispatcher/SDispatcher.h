/**
 * ------------------------------------------------------------------------------------------------
 * File:   SDispacher.h
 * Author: Luis Monteiro
 *
 * Created on February 3, 2020, 21:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDISPATCHER_H
#define SDISPATCHER_H

#include <map>

namespace Helper {

	template<typename Key, typename Callable>
	class SDispatcher {
	public:

		void emplace(Key id, Callable callable) {
			__container.emplace(id, callable);
		}

		template <class... Args>
		auto operator()(const Key& id, Args&&... args) {
			return _invoke(__container.at(id), std::forward<Args>(args)...);
		}
		
	protected:
		template<typename T> 
		struct is_shared_ptr : std::false_type {};
		template <typename T>
		struct is_shared_ptr<std::shared_ptr<T> > : std::true_type {};
		
		template <typename C, class... A, 
			std::enable_if_t<is_shared_ptr<C>::value, int> = 0>
		auto _invoke(C& callable, A&&... args) {
			return (*callable)(std::forward<A>(args)...);
		}

		template <typename C, class... A,
			std::enable_if_t<!is_shared_ptr<C>::value, int> = 0>
		auto _invoke(C& callable, A&&... args){
			return ( callable)(std::forward<A>(args)...);
		} 
	private:
		std::map<Key, Callable> __container;
	};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif