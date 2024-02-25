#pragma once
#include "Types.h"
#include "Allocator.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <deque>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template<typename Type>
using xvector = vector<Type, STLAllocator<Type>>;
template<typename Type>
using Vector = vector<Type, STLAllocator<Type>>;

template<typename Type>
using xlist = list<Type, STLAllocator<Type>>;
template<typename Type>
using List = list<Type, STLAllocator<Type>>;

template<typename Key, typename Type, typename Pred = less<Key>>
using xmap = map<Key, Type, Pred, STLAllocator<pair<const Key, Type>>>;
template<typename Key, typename Type, typename Pred = less<Key>>
using Map = map<Key, Type, Pred, STLAllocator<pair<const Key, Type>>>;

template<typename Key, typename Pred = less<Key>>
using xset = set<Key,Pred, STLAllocator<Key>>;
template<typename Key, typename Pred = less<Key>>
using Set = set<Key, Pred, STLAllocator<Key>>;

template<typename Type>
using xdeque = deque<Type, STLAllocator<Type>>;
template<typename Type>
using Deque = deque<Type, STLAllocator<Type>>;

template<typename Type, typename Container = xdeque<Type>>
using xqueue = queue<Type, Container>;
template<typename Type, typename Container = xdeque<Type>>
using Queue = queue<Type, Container>;

template<typename Type, typename Container = xdeque<Type>>
using xstack = stack<Type, Container>;
template<typename Type, typename Container = xdeque<Type>>
using Stack = stack<Type, Container>;

template<typename Type, typename Container = xvector<Type>,typename Pred = less<typename Container::value_type>>
using xpriority_queue = priority_queue<Type, Container,Pred>;
template<typename Type, typename Container = xvector<Type>, typename Pred = less<typename Container::value_type>>
using PriorityQueue = priority_queue<Type, Container, Pred>;

using String = basic_string<char, char_traits<char>, STLAllocator<char>>;
using WString = basic_string<wchar_t, char_traits<wchar_t>, STLAllocator<wchar_t>>;

template<typename Key, typename Type, typename Hasher = hash<Key>, typename KeyEq = equal_to<Key>>
using HashMap = unordered_map<Key, Type, Hasher, KeyEq, STLAllocator<pair<const Key, Type>>>;

template<typename Key,  typename Hasher = hash<Key>, typename KeyEq = equal_to<Key>>
using HashSet = unordered_set<Key, Hasher, KeyEq, STLAllocator<Key>>;