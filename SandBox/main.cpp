#include <iostream>
#include <memory>

struct Collar
{

	enum class TYPE
	{
		PLASTIC,
		LEATHER
	};
	Collar(const TYPE& type_, const std::string colorName_) :
		colorName(colorName_), type(type_)
	{
	}
	//Data
	std::string colorName;
	TYPE type;
};

class Dog
{

public:
	

	Dog(const Collar::TYPE& type_, const std::string colorName_, const std::string dogName_) :
		poCollar(new Collar(type_, colorName_)), dogName(dogName_)
	{

	}

	Dog& operator=(const Dog& dog)
	{
		if (this != &dog)
		{

			try
			{				
				Collar* pOrigCollar = new Collar(dog.poCollar->type, dog.poCollar->colorName);
				delete this->poCollar;
				this->poCollar = pOrigCollar;
				this->dogName = dog.dogName;
				
			}

			catch (const std::bad_alloc& st)
			{
				std::cout << "Memory allocation issue occurs: "<< st.what() << '\n';
				return *this;
			}
		}
		return *this;
	}
	Dog(const Dog& dog)
	{
		this->poCollar = new Collar(dog.poCollar->type, dog.poCollar->colorName);
		this->dogName = dog.dogName;
	}
	~Dog()
	{
		delete this->poCollar;
	}
	//Composition relationship between Dog and Collar
	//The pointer is owned by the class Dog
	/*
	
	This means that the Dog class contains an instance of the Collar class as one of its properties or attributes. 
	In other words, a Dog has a Collar, and the Collar belongs to that specific Dog. 
	This is a form of "has-a" relationship, where one class contains an instance of another class.
	*/
	Collar* poCollar; //pointer owned
	std::string dogName;
};


int main()
{

	
	Dog coco(Collar::TYPE::LEATHER, "Pink", "Coco");
	Dog miko(Collar::TYPE::LEATHER, "Blue", "Miko");
	Dog candy(Collar::TYPE::LEATHER, "Yellow", "Candy");

	Dog zizi(coco);

	{
		Dog yummy(Collar::TYPE::LEATHER, "Yellow", "Yummy");
		yummy = miko;
	}
	miko = zizi;
	coco = candy;
	std::cout << miko.dogName << '\n';
	miko = miko;
	std::cout << miko.dogName << '\n';
	std::cout << coco.dogName << '\n';
	coco = coco;
	std::cout << coco.dogName << '\n';



	return 0;
}


