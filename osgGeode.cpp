#include <osg/Geode>
#include <iostream>

class GeodeParent
{
public:
	GeodeParent() {}

	void setGeode(osg::Geode* geode) { _geode = geode; }
	osg::Geode* getGeode() { return _geode.get(); }

protected:
	osg::ref_ptr<osg::Geode> _geode;
	

};
int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
	osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;

	GeodeParent geodeParent;
	geodeParent.setGeode(geode1);

	std::cout << "Count 1 Before: " << geode1->referenceCount() << std::endl;
	std::cout << "Count 2 Before: " << geode2->referenceCount() << std::endl;

	geodeParent.setGeode(geode2);

	std::cout << "Count 1 After: " << geode1->referenceCount() << std::endl;
	std::cout << "Count 2 After: " << geode1->referenceCount() << std::endl;
	return 0;
}
