#include "vector.hpp"
#include <iostream>

Vector::Vector(const Vector& other):
            m_size{other.m_size},
            m_cap{other.m_cap},
            m_buf{}
{
    if (!other.empty()) {
        m_buf = new int[m_cap];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = other.m_buf[i];
        }
    }
}

Vector::Vector(const Vector&& other):
            m_size{other.m_size},
            m_cap{other.m_cap},
            m_buf{}
{
    if (!other.empty()) {
        m_buf = new int[m_cap];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = std::move(other.m_buf[i]);
        }
    }
}

Vector::Vector(size_t cap)
{
    m_size = 0;
    m_cap = cap;
    m_buf = new int[cap];
}

Vector::Vector(std::initializer_list<int> init)
{
    m_cap = init.size();
    m_buf = new int[init.size()];
    std::initializer_list<int>::iterator it = init.begin();
    for (size_t i{}; i < init.size(); ++i) {
        this->push_back(*it++);
        m_size++;
    }
}

Vector::~Vector()
{
    delete m_buf;
    m_buf = nullptr;
}

Vector& Vector::operator=(const Vector& oth)
{
    if (&oth == this) {
        return *this;
    }
    if (!oth.empty()) {
        m_size = oth.m_size;
        m_cap  = oth.m_cap;    
        m_buf = new int[m_cap];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = oth.m_buf[i];
        }
    }
    return *this;
}
Vector& Vector::operator=(const Vector&& oth)
{
    if (&oth == this) {
        return *this;
    }
    if (!oth.empty()) {
        m_size = std::move(oth.m_size);
        m_cap = std::move(oth.m_cap);    
        m_buf = new int[m_cap];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = std::move(oth.m_buf[i]);
        }
    }
    return *this;
}

Vector& Vector::operator+(Vector& other)
{
    if (other.empty()) {
        return *this;
    }
    if (this->empty()) {
        return other;
    }
    int* tmp = new int[m_size];
    for (size_t i{}; i < (m_size <= other.m_size)? m_size : other.m_size; ++i) {
        tmp[i] = m_buf[i] + other.m_buf[i];
    }
    delete m_buf;
    m_buf = tmp;
    tmp = nullptr;
    return *this;
}

void Vector::operator+=(Vector& oth)
{
    m_cap += oth.m_cap;
    int* tmp = new int[m_cap];
	for (size_t i{}; i < m_size; ++i){
		tmp[i] = m_buf[i];
	}
    size_t old = m_size;
    m_size += oth.m_size;
    for (size_t i{}; i < oth.m_size; ++i){
		tmp[old + i] = oth.m_buf[i];
	}
    delete[] m_buf;
	m_buf = tmp;
	tmp = nullptr;
}

int& Vector::operator[](size_t index)
{
	return m_buf[index];
}

const int& Vector::operator[](size_t index) const
{
	return m_buf[index];
}

void Vector::push_back(const int& val)
{
   if (this->empty()) {
       m_buf = new int[m_cap];
       m_buf[m_size++] = val;
   }
   else if(m_size < m_cap) {
       m_buf[m_size++] = val;
   }
   else {
        m_cap *= 2;
        int* tmp = new int[m_cap];
        for (size_t i{}; i < m_size; ++i) {
            tmp[i] = m_buf[i];
            delete m_buf;
            m_buf = tmp;
            tmp = nullptr;
            m_buf[m_size++] = val;
        }
   }
}

void Vector::push_back(const int&& val)
{
	if(this->empty()){
		m_buf = new int[m_cap];
		m_buf[m_size++] = std::move(val);
	}else{
		if (m_size < m_cap){
			m_buf[m_size++] = std::move(val);
		}else{
			m_cap *= 2;
			int* tmp = new int[m_cap];
			for(size_t i{}; i < m_size; ++i){
				tmp[i] = std::move(m_buf[i]);
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			m_buf[m_size++] = std::move(val);
		}
	}
}

void Vector::insert(size_t pos, const int& val)
{
	if (this->empty()){
		m_buf = new int[m_cap];
		m_buf[0] = val;
	}else{
		if(m_size < m_cap){
			for (size_t i{pos}; i < m_size; ++i){
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = val;
			++m_size;
		}else{
			m_cap *= 2;
			int* tmp = new int[m_cap];
			for (size_t i{}; i < pos; ++i){
				tmp[i] = m_buf[i];
			}
			tmp[pos] = val;
			for (size_t i{pos}; i < m_size; ++i){
				tmp[i + 1] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

void Vector::insert(size_t pos,const int&& val)
{
	if (this->empty()){
		m_buf = new int[m_cap];
		m_buf[0] = std::move(val);
	}else{
		if(m_size < m_cap){
			for (size_t i{pos}; i < m_size; ++i){
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = std::move(val);
			++m_size;
		}else{
			m_cap *= 2;
			int* tmp = new int[m_cap];
			for (size_t i = 0; i < pos; ++i){
				tmp[i] = m_buf[i];
			}
			tmp[pos] = std::move(val);
			for (size_t i{pos}; i <m_size; ++i){
				tmp[i + 1] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

bool Vector::empty() const
{
    return !m_buf;
}

size_t Vector::find_by_value(const int& val)
{
    if (!this->empty()) {
        for (size_t i{}; i < m_size; ++i) {
            if (m_buf[i] == val) {
                return i;
            }
        }
    }
    return -1;
}

size_t Vector::remove_by_value(const int& val)
{
    if (!this->empty()) {
        size_t pos = find_by_value(val);
        if (pos != -1) {
            for (size_t i {pos}; i < m_size; ++i){
			    m_buf[i - 1] = m_buf[i];
		    }
		    --m_size;
            return pos;
        }
    }
    return -1;
}

void Vector::pop_back()
{
	if(!this->empty()){
		--m_size;
	}
}
