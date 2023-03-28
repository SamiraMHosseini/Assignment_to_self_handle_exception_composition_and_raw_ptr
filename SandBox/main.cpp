#include <iostream>
#include <memory>

class Collar
{
public:
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
	Dog(Collar* pCollar_, const std::string dogName_) :

		Dog(pCollar_->type, pCollar_->colorName, dogName_)
	{

	}

	Dog(const Collar::TYPE& type_, const std::string colorName_, const std::string dogName_) :
		pCollar(new Collar(type_, colorName_)), dogName(dogName_)
	{

	}

	Dog& operator=(const Dog& dog)
	{
		if (this != &dog)
		{

			try
			{				
				Collar* pOrigCollar = new Collar(dog.pCollar->type, dog.pCollar->colorName);
				delete this->pCollar;
				this->pCollar = pOrigCollar;
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
		this->pCollar = new Collar(dog.pCollar->type, dog.pCollar->colorName);
		this->dogName = dog.dogName;
	}
	~Dog()
	{
		delete this->pCollar;
	}

	Collar* pCollar; //A dog has a Collar object
	std::string dogName;
};


int main()
{

	Collar* collarPink = new Collar(Collar::TYPE::LEATHER, "Pink");

	Collar* collarBlue = new Collar(Collar::TYPE::PLASTIC, "Blue");
	Dog coco(collarPink, "Coco");
	Dog miko(collarBlue, "Miko");
	Dog Candy(collarBlue, "Candy");
	Dog Zizi(Candy);

	{
		Dog candy(collarBlue, "Candy");
		candy = miko;
	}

	std::cout << miko.dogName << '\n';
	miko = miko;
	std::cout << miko.dogName << '\n';


	Collar c2(Collar::TYPE::LEATHER, "Yellow");
	Dog coco2(&c2, "Yummy");

	delete collarBlue;
	delete collarPink;

	return 0;
}


