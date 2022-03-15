
#include <jsg/Viewer.h>

int main(int argc, char** argv)
{
	jsg::Viewer v;
	v.setClearColor(glm::dvec4(1.0, 0.0, 0.0, 0.0));
	v.run();

}