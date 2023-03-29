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

	Collar* pCollar; //Composition relationship between Dog and Collar
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


