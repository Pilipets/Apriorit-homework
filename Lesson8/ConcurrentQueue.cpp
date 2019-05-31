#include "ConcurrentQueue.h"

template class ConcurrentQueue<int>;
template<class T>
ConcurrentQueue<T>::ConcurrentQueue(size_t max_size):
	_max_size(max_size), _state(State::OPEN)
{}

template<class T>
ConcurrentQueue<T>::ConcurrentQueue(): _state(State::OPEN)
{}

template<class T>
ConcurrentQueue<T>::~ConcurrentQueue()
{
	std::unique_lock<std::mutex> lk(_mtx);
	if (_state == State::CLOSED)
		return;
	_state = State::CLOSED;
	std::queue<T> q;
	swap(q, _data);

	//maybe we should wait for all executed threads
}
template<class T>
ConcurrentQueue<T>::ConcurrentQueue(const ConcurrentQueue & source) :
	_data(source._data), _max_size(source._max_size), _state(State::OPEN)
{}

template<class T>
void ConcurrentQueue<T>::push(T &&value) {
	std::unique_lock<std::mutex> lk(_mtx);
	_cond_not_full.wait(lk, [this]() {return _data.size() != _max_size; });

	if (_state == State::CLOSED)
		return;
	_data.emplace(std::move(value));
	lk.unlock();
	_cond_not_empty.notify_one();
}

template<class T>
void ConcurrentQueue<T>::push(const T &value)
{
	std::unique_lock<std::mutex> lk(_mtx);
	_cond_not_full.wait(lk, [this]() {return _data.size() != _max_size; });
	if (_state == State::CLOSED)
		return;

	_data.push(value);
	lk.unlock();
	_cond_not_empty.notify_one();
}

template<class T>
void ConcurrentQueue<T>::pop() {
	std::unique_lock<std::mutex> lk(_mtx);
	while (_data.empty() && _state != State::CLOSED)
		_cond_not_empty.wait(lk);
	if (_data.empty() && _state == State::CLOSED)
		return;

	T result = std::move(_data.front());
	_data.pop();

	lk.unlock();
	_cond_not_full.notify_one();
}

template<class T>
bool ConcurrentQueue<T>::try_pop(T & dst)
{
	std::unique_lock<std::mutex> lk(_mtx);

	while (_data.empty() && _state != State::CLOSED)
		_cond_not_empty.wait(lk);

	if (_data.empty() && _state == State::CLOSED)
		return false;
	else{
		dst = std::move(_data.front());
		_data.pop();
		lk.unlock();
		_cond_not_full.notify_one();
		return true;
	}
}

template<class T>
void ConcurrentQueue<T>::clear()
{
	std::unique_lock<std::mutex> lk(_mtx);
	if (_state == State::CLOSED)
		return;
	std::queue<T> q;
	swap(q, _data);

	lk.unlock();
	_cond_not_full.notify_all();
}

template<class T>
void ConcurrentQueue<T>::close()
{
	std::unique_lock<std::mutex> lock(_mtx);
	_state = State::CLOSED;

	// Notify all consumers.
	lock.unlock();
	_cond_not_empty.notify_all();
}

template<class T>
inline size_t ConcurrentQueue<T>::size() const
{
	return _data.size();
}
