// -*-c++-*-

/*
 * Draw an outline around a model.
 */

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgFX/Outline>

class ClickHandler : public osgGA::GUIEventHandler
{
public:
	ClickHandler(osgFX::Outline* outline) : _outline(outline) {}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
	{
		switch (ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::PUSH):
		{
			_outline->setEnabled(!_outline->getEnabled());
			return true;
		}
		default:
			return false;
		}
	}

private:
	osg::ref_ptr<osgFX::Outline> _outline;
};

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName() + " [options] <file>");
	arguments.getApplicationUsage()->addCommandLineOption("-h or --help", "Display this information");


	// load outlined object
	std::string modelFilename = arguments.argc() > 1 ? arguments[1] : "dumptruck.osgt";
	osg::ref_ptr<osg::Node> outlineModel = osgDB::readRefNodeFile(modelFilename);
	if (nullptr == outlineModel)
	{
		return -1;
	}

	// create scene
	osg::ref_ptr<osg::Group> pRoot = new osg::Group;

	// create outline effect
	osg::ref_ptr<osgFX::Outline> pOutLine = new osgFX::Outline;

	pRoot->addChild(pOutLine);

	pOutLine->setWidth(8);
	pOutLine->setColor(osg::Vec4(1, 1, 0, 1));
	pOutLine->addChild(outlineModel);

	// must have stencil buffer...
	osg::DisplaySettings::instance()->setMinimumNumStencilBits(1);

	// construct the viewer
	osgViewer::Viewer viewer;
	viewer.setSceneData(pRoot);

	pOutLine->setEnabled(false); // 初始状态不高亮
	viewer.addEventHandler(new ClickHandler(pOutLine.get())); // 添加事件处理器

	// must clear stencil buffer...
	unsigned int clearMask = viewer.getCamera()->getClearMask();
	viewer.getCamera()->setClearMask(clearMask | GL_STENCIL_BUFFER_BIT);
	viewer.getCamera()->setClearStencil(0);

	return viewer.run();
}