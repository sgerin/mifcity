#include "ObjManager.h"

#include <string>

void ObjManager::writeToObj(const Mesh& m, const char* file)
{
	std::ofstream f(file, std::ios::out);

	if (!file)
	{
		std::cerr << "Cannot open " << file << std::endl;
		return;
	}

	for(unsigned int i=0; i < m.getVertices().size(); i++)
	{
        f << "v " << m.getVertices()[i].location[0]
          << " " << m.getVertices()[i].location[1]
          << " " << m.getVertices()[i].location[2]<< std::endl;
	}
	
	// write all textures coordinates used by vertices

	std::vector<Face>::const_iterator it;
	for(it = m.faces.begin(); it != m.faces.end(); it++)
	{
		f << "f " << it->vertices[0] + 1 <<
		     " " << it->vertices[1] + 1 <<
		     " " << it->vertices[2] + 1 << std::endl;
	}

	//  f v1/vt1 v2/vt2 v3/vt3 ...
	// vt1 represents a texture index from the previous list. touch s


	/*for(unsigned int i = 0; i < m.getIndexes().size(); i+=3)
	{
		//Due to obj starting @ index 1
		f << "f " << m.getIndexes()[i] + 1
		<< " " << m.getIndexes()[i+1] + 1
		<< " " << m.getIndexes()[i+2] + 1<< std::endl;
	}*/

	std::cout << "Written to file " << file << std::endl;

	f.close();
}

double readDouble(std::string s, int& i)
{
	double r = 0;
	double divide = 0;
	int sign = 1;
	
	while(	(s[i] >= '0' && s[i] <= '9') ||
		(s[i] == '.') ||
		(s[i] == '-') )
	{
		if (s[i] == '.')
		{
			divide = 1;
			i++;
			continue;
		}
		if (s[i] == '-')
		{
			sign = -1;
			i++;
			continue;
		}
		
		divide *= 10;
		r *= 10;
		r += s[i]-'0';
		i++;
	}
	i++;

	if (divide == 0)
		divide = 1;

	return r/divide * sign;
}

int readInt(std::string s, int& i)
{
	double r = 0;
	while(s[i] >= '0' && s[i] <= '9')
	{
		r *= 10;
		r += s[i]-'0';
		i++;
	}
	i++;
	return r;
}

Mesh* ObjManager::createFromObj(const char* file)
{
    std::ifstream f(file, std::ios::in);
	std::string line;
	std::string val_string;

	Mesh* m = new Mesh;
	
    if (!f)
	{
		std::cerr << "Cannot open " << file << std::endl;
		return m;
	}

	while ( !f.eof() )
	{
		getline (f,line);

		if (line.empty())
			break;

		int i = 0;
		val_string = line.substr(2);
		switch(line[0])
		{
			case 'v':
			{
				double x = readDouble(val_string, i);
				double y = readDouble(val_string, i);
				double z = readDouble(val_string, i);
				m->addVertex(Vector(x, y, z));
				break;
			}
			case 'f':
			{
				int a = readInt(val_string, i) - 1;
				int b = readInt(val_string, i) - 1;
				int c = readInt(val_string, i) - 1;
				m->addFace(a, b, c);

				break;
			}
			default:
				break;
		}
	}

	f.close();

	return m;
}
