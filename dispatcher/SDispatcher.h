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

		void add_callable(Key id, Callable callable) {
			__container.emplace(id, callable);
		}

		template <class... Args>
		auto invoke(const Key& id, Args&&... args) {
			return __container.at(id)(std::forward<Args>(args)...);
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