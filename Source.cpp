#include <iostream>

class String {
	public:
		/// <summary>
		///Parameterised Constructor 
		/// </summary>
		/// <param name="str"></param>
		String(const char* str)
		{
			m_size = strlen(str);
			m_data = new char[m_size];
			memcpy(m_data,str, m_size);
			std::cout << "constructed" << std::endl;
		}
		
		~String() {
			delete m_data;
			std::cout<<"destroyed"<<std::endl;
		}
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="S"></param>
		String(const String& S) {
			m_size = S.m_size;
			m_data = new char[m_size];
			memcpy(m_data, S.m_data, m_size);
			std::cout << "copied" << std::endl;
		}
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="stream"></param>
		/// <param name="S"></param>
		/// <returns></returns>
		String(String&& S) noexcept{
			m_size = S.m_size;
			m_data = S.m_data;
			S.m_data = nullptr;
			std::cout << "Moved" << std::endl;
		}
		friend std::ostream& operator<<(std::ostream& stream, const String& S);
private:
	char* m_data;
	int m_size;
};

class Entity{
public:
	/// <summary>
	/// lValue Constructor
	/// </summary>
	/// <param name="name"></param>
	Entity(const String& name) 
		:m_name(name)
	{
		std::cout << "l-Entity" << std::endl;
	}
	/// <summary>
	/// rValue Constructor
	/// </summary>
	/// <param name="name"></param>
	Entity(String&& name) 
		:m_name(std::move(name))
	{
		std::cout << "r-Entity" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& stream, const Entity& E);

private:
	String m_name;
};

std::ostream& operator<<(std::ostream& stream, const String& S) {
	stream << S.m_data << std::endl;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Entity& E) {
	stream << E.m_name << std::endl;
	return stream;
}

int main() {
	String S("char");
	Entity E(std::move(S));
	std::cout << E << std::endl;
}