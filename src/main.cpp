#include <math.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "mikktspace.h"

struct Face {
	size_t a;
	size_t b;
	size_t c;
};

struct Vector2 {
	float x;
	float y;
};

std::ostream& operator<<(std::ostream& s, const Vector2& v) {
	return s << "[" << v.x << ", " << v.y << "]";
}

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3 normalized() {
		return (*this) / sqrt(x * x + y * y + z * z);
	}

	Vector3 operator/(float rhs) {
		return Vector3{x / rhs, y / rhs, z / rhs};
	}
};

std::ostream& operator<<(std::ostream& s, const Vector3& v) {
	return s << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

struct Vertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
};

struct Mesh {
	std::vector<Face> faces;
	std::vector<Vertex> vertices;

	void dumpObj(std::ostream& out) {
		for (Vertex vtx : vertices) {
			out << "v " << vtx.position.x << " " << vtx.position.y << " "
			    << vtx.position.z << std::endl;
		}

		for (Vertex vtx : vertices) {
			out << "vn " << vtx.normal.x << " " << vtx.normal.y << " "
			    << vtx.normal.z << std::endl;
		}

		for (Vertex vtx : vertices) {
			out << "vt " << vtx.texCoord.x << " " << vtx.texCoord.y
			    << std::endl;
		}

		for (Face face : faces) {
			out << "f " << (face.a + 1) << " " << (face.b + 1) << " "
			    << (face.c + 1) << std::endl;
		}
	}

	static Mesh makeCube() {
		struct ControlPoint {
			Vector2 uv;
			Vector3 dir;
		};

		std::vector<Face> faces;
		std::vector<ControlPoint> ctlPts;
		std::vector<Vertex> vertices;

		// +x plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{0.0, 0.0}, {1.0, -1.0, 1.0}});
			ctlPts.push_back({{0.0, 1.0}, {1.0, -1.0, -1.0}});
			ctlPts.push_back({{1.0, 1.0}, {1.0, 1.0, -1.0}});
			ctlPts.push_back({{1.0, 0.0}, {1.0, 1.0, 1.0}});
			ctlPts.push_back({{0.5, 0.5}, {1.0, 0.0, 0.0}});
		}

		// -x plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{1.0, 0.0}, {-1.0, 1.0, 1.0}});
			ctlPts.push_back({{1.0, 1.0}, {-1.0, 1.0, -1.0}});
			ctlPts.push_back({{0.0, 1.0}, {-1.0, -1.0, -1.0}});
			ctlPts.push_back({{0.0, 0.0}, {-1.0, -1.0, 1.0}});
			ctlPts.push_back({{0.5, 0.5}, {-1.0, 0.0, 0.0}});
		}

		// +y plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{0.0, 0.0}, {1.0, 1.0, 1.0}});
			ctlPts.push_back({{0.0, 1.0}, {1.0, 1.0, -1.0}});
			ctlPts.push_back({{0.0, 1.0}, {-1.0, 1.0, -1.0}});
			ctlPts.push_back({{0.0, 0.0}, {-1.0, 1.0, 1.0}});
			ctlPts.push_back({{0.0, 0.5}, {0.0, 1.0, 0.0}});
		}

		// -y plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{0.0, 0.0}, {-1.0, -1.0, 1.0}});
			ctlPts.push_back({{0.0, 1.0}, {-1.0, -1.0, -1.0}});
			ctlPts.push_back({{0.0, 1.0}, {1.0, -1.0, -1.0}});
			ctlPts.push_back({{0.0, 0.0}, {1.0, -1.0, 1.0}});
			ctlPts.push_back({{0.0, 0.5}, {0.0, -1.0, 0.0}});
		}

		// +z plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{0.0, 0.0}, {-1.0, 1.0, 1.0}});
			ctlPts.push_back({{0.0, 1.0}, {-1.0, -1.0, 1.0}});
			ctlPts.push_back({{1.0, 1.0}, {1.0, -1.0, 1.0}});
			ctlPts.push_back({{1.0, 0.0}, {1.0, 1.0, 1.0}});
			ctlPts.push_back({{0.5, 0.5}, {0.0, 0.0, 1.0}});
		}

		// -z plane
		{
			size_t base = ctlPts.size();
			faces.push_back({base, base + 1, base + 4});
			faces.push_back({base + 1, base + 2, base + 4});
			faces.push_back({base + 2, base + 3, base + 4});
			faces.push_back({base + 3, base, base + 4});
			ctlPts.push_back({{1.0, 0.0}, {1.0, 1.0, -1.0}});
			ctlPts.push_back({{1.0, 1.0}, {1.0, -1.0, -1.0}});
			ctlPts.push_back({{0.0, 1.0}, {-1.0, -1.0, -1.0}});
			ctlPts.push_back({{0.0, 0.0}, {-1.0, 1.0, -1.0}});
			ctlPts.push_back({{0.5, 0.5}, {0.0, 0.0, -1.0}});
		}

		for (auto pt : ctlPts) {
			Vector3 p = pt.dir;
			Vector3 n = p.normalized();
			Vector2 t = pt.uv;

			vertices.push_back(Vertex{
			    (p / 2.0),
			    n,
			    Vector2{t.x, t.y},
			});
		}

		Mesh m;
		m.faces    = faces;
		m.vertices = vertices;
		return m;
	}
};

struct Result {
	Vector3 tangent;
	Vector3 biTangent;
	float magS;
	float magT;
	bool isOrientationPreserving;
	int face;
	int vert;
};

struct MyContext {
	Mesh mesh;
	std::vector<Result> results;
	void (*printFunction)(MyContext&, std::ostream&);
};

Vertex* vertex(Mesh* m, size_t face, size_t vert) {
	Face f = m->faces[face];

	switch (vert) {
	case 0:
		return &m->vertices[f.a];
	case 1:
		return &m->vertices[f.b];
	case 2:
		return &m->vertices[f.c];
	default:
		std::cerr << "Unexpected vert value: " << vert << std::endl;
		exit(1);
	}
}

int getNumFaces(const SMikkTSpaceContext* context) {
	Mesh* m = &((MyContext*)context->m_pUserData)->mesh;
	return m->faces.size();
}

int getNumVerticesOfFace(const SMikkTSpaceContext* context, const int face) {
	return 3;
}

void getPosition(
    const SMikkTSpaceContext* context,
    float posOut[],
    const int face,
    const int vert) {
	Mesh* m   = &((MyContext*)context->m_pUserData)->mesh;
	Vertex v  = *vertex(m, face, vert);
	posOut[0] = v.position.x;
	posOut[1] = v.position.y;
	posOut[2] = v.position.z;
}

void getNormal(
    const SMikkTSpaceContext* context,
    float normOut[],
    const int face,
    const int vert) {
	Mesh* m    = &((MyContext*)context->m_pUserData)->mesh;
	Vertex v   = *vertex(m, face, vert);
	normOut[0] = v.normal.x;
	normOut[1] = v.normal.y;
	normOut[2] = v.normal.z;
}

void getTexCoord(
    const SMikkTSpaceContext* context,
    float texcOut[],
    const int face,
    const int vert) {
	Mesh* m    = &((MyContext*)context->m_pUserData)->mesh;
	Vertex v   = *vertex(m, face, vert);
	texcOut[0] = v.texCoord.x;
	texcOut[1] = v.texCoord.y;
}

void setTSpace(
    const SMikkTSpaceContext* context,
    const float tangent[],
    const float biTangent[],
    const float magS,
    const float magT,
    const tbool bIsOrientationPreserving,
    const int face,
    const int vert) {
	MyContext* mc = (MyContext*)context->m_pUserData;
	mc->results.push_back(
	    Result{Vector3{tangent[0], tangent[1], tangent[2]},
	           Vector3{biTangent[0], biTangent[1], biTangent[2]},
	           magS,
	           magT,
	           !!bIsOrientationPreserving,
	           face,
	           vert});
}

void printResultsRust(MyContext& mc, std::ostream& out) {
	for (Result r : mc.results) {
		out << "Result::new(" << r.tangent << ", " << r.biTangent << ", "
		    << r.magS << ", " << r.magT << ", "
		    << (r.isOrientationPreserving ? "true" : "false") << ", " << r.face
		    << ", " << r.vert << ")," << std::endl;
	}
}

void printResultsObj(MyContext& mc, std::ostream& out) {
	mc.mesh.dumpObj(out);
}

int main(int argc, const char** argv) {
	std::cout.precision(8);
	std::cout << std::fixed;

	const char* argument = "rust";
	if (argc >= 2) {
		argument = argv[1];
	}

	MyContext mc;
	mc.mesh = Mesh::makeCube();

	if (strcmp(argument, "obj") == 0) {
		mc.printFunction = printResultsObj;
	} else {
		mc.printFunction = printResultsRust;
	}

	SMikkTSpaceInterface interface;
	interface.m_getNumFaces          = getNumFaces;
	interface.m_getNumVerticesOfFace = getNumVerticesOfFace;
	interface.m_getPosition          = getPosition;
	interface.m_getNormal            = getNormal;
	interface.m_getTexCoord          = getTexCoord;
	interface.m_setTSpaceBasic       = nullptr;
	interface.m_setTSpace            = setTSpace;

	SMikkTSpaceContext context;
	context.m_pInterface = &interface;
	context.m_pUserData  = &mc;

	genTangSpaceDefault(&context);
	mc.printFunction(mc, std::cout);

	return EXIT_SUCCESS;
}
