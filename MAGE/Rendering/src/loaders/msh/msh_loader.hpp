#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the mesh from the given MSH file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the MSH filename.
	 @param[out]	vertices
					A reference to a vector containing the vertices of the 
					mesh.
	 @param[out]	indices
					A reference to a vector containing the indices of the mesh.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportMSHMeshFromFile(const wstring& fname, 
		                       std::vector< VertexT >& vertices, 
		                       std::vector< IndexT > & indices);

	/**
	 Exports the given mesh to the given MSH file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the MSH filename.
	 @param[in]		vertices
					A reference to a vector containing the vertices of the 
					mesh.
	 @param[in]		indices
					A reference to a vector containing the indices of the mesh.
	 @throws		Exception
					Failed to export the mesh to file.
	 */
	template< typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const wstring& fname, 
		                     const std::vector< VertexT >& vertices, 
		                     const std::vector< IndexT > & indices);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_loader.tpp"

#pragma endregion