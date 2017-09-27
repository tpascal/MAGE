#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_reader.hpp"
#include "mesh\msh\msh_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	void ImportMSHMeshFromFile(const wstring &fname,
		vector< VertexT > &vertices, vector < u32 > &indices) {
		
		MSHReader< VertexT, u32 > reader(vertices, indices);
		reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	void ExportMSHMeshToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< u32 > &indices) {
		
		MSHWriter< VertexT, u32 > writer(vertices, indices);
		writer.WriteToFile(fname);
	}
}