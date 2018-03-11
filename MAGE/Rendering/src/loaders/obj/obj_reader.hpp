#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "resource\model\model_output.hpp"
#include "resource\mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {
	// Forward declaration.
	class ResourceManager;
}

namespace mage::rendering::loader {

	/**
	 A class of OBJ file readers for reading meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	class OBJReader final : private LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an OBJ reader.

		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		model_output
						A reference to a model output for storing the read data 
						from file.
		 @param[in]		mesh_desc
						A reference to a mesh descriptor.
		 */
		explicit OBJReader(ResourceManager& resource_manager, 
						   ModelOutput< VertexT, IndexT >& model_output, 
						   const MeshDescriptor< VertexT, IndexT >& mesh_desc);
		
		/**
		 Constructs an OBJ reader from the given OBJ reader.

		 @param[in]		reader
						A reference to the OBJ reader to copy.
		 */
		OBJReader(const OBJReader& reader) = delete;

		/**
		 Constructs an OBJ reader by moving the given OBJ reader.

		 @param[in]		reader
						A reference to the OBJ reader to move.
		 */
		OBJReader(OBJReader&& reader) noexcept;

		/**
		 Destructs this OBJ reader.
		 */
		~OBJReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given OBJ reader to this OBJ reader.

		 @param[in]		reader
						A reference to a OBJ reader to copy.
		 @return		A reference to the copy of the given OBJ reader (i.e. 
						this OBJ reader).
		 */
		OBJReader& operator=(const OBJReader& reader) = delete;

		/**
		 Moves the given OBJ reader to this OBJ reader.

		 @param[in]		reader
						A reference to a OBJ reader to move.
		 @return		A reference to the moved OBJ reader (i.e. this OBJ 
						reader).
		 */
		OBJReader& operator=(OBJReader&& reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using LineReader::ReadFromFile;

		using LineReader::ReadFromMemory;

		using LineReader::GetFilename;

		using LineReader::GetDelimiters;

	private:

		//---------------------------------------------------------------------
		// Type Declarations and Definitions
		//---------------------------------------------------------------------

		/**
		 A struct of three indices.
		 */
		using Index3 = Vector3< IndexT >;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Pre-process before reading the current file of this OBJ reader.

		 @throws		Exception
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess() override;

		/**
		 Reads the given line.

		 @param[in,out] line
						A pointer to the null-terminated string to read.
		 @throws		Exception
						Failed to read the given line.
		 */
		virtual void ReadLine(NotNull< zstring > line) override;

		/**
		 Post-processes after reading the current file of this OBJ reader.

		 @throws		Exception
						Failed to finish post-processing successfully.
		 */
		virtual void Postprocess() override;

		/**
		 Reads a Material Library Include definition.

		 @throws		Exception
						Failed to read a Material Library Include definition.
		 */
		void ReadOBJMaterialLibrary();

		/**
		 Reads a Material Usage definition and imports the materials 
		 corresponding to the mesh.

		 @throws		Exception
						Failed to read a Material Usage definition.
		 @throws		Exception
						Failed to import the materials.
		 */
		void ReadOBJMaterialUse();

		/**
		 Reads a Group definition.

		 @throws		Exception
						Failed to read a Group definition.
		 */
		void ReadOBJGroup();

		/**
		 Reads an Object definition.

		 @throws		Exception
						Failed to read a Object definition.
		 */
		void ReadOBJObject();

		/**
		 Reads a Smoothing Group definition.

		 @note			A smoothing group is, if present, 
						silently ignored.
		 @throws		Exception
						Failed to read a Smoothing Group definition.
		 */
		void ReadOBJSmoothingGroup();

		/**
		 Reads a Vertex Position Coordinates definition.

		 @throws		Exception
						Failed to read a Vertex Position Coordinates 
						definition.
		 */
		void ReadOBJVertex();

		/**
		 Reads a Vertex Texture Coordinates definition.

		 @note			Only UV texture coordinates are supported,
						The W component of UVW texture coordinates
						is, if present, silently ignored.
		 @throws		Exception
						Failed to read a Vertex Texture Coordinates definition.
		 */
		void ReadOBJVertexTexture();

		/**
		 Reads a Vertex Normal Coordinates definition.

		 @pre			All the vertex normals in the OBJ file are normalized.
		 @throws		Exception
						Failed to read a Vertex Normal Coordinates definition.
		 */
		void ReadOBJVertexNormal();

		/**
		 Reads a Face definition.

		 @throws		Exception
						Failed to read a Face definition.
		 */
		void ReadOBJFace();

		/**
		 Reads a set of vertex position coordinates.

		 @return		The @c Point3 represented by the next token of this OBJ 
						reader (modified according to the mesh descriptor of 
						this OBj reader).
		 @throws		Exception
						Failed to read a @c Point3.
		 */
		[[nodiscard]]
		const Point3 ReadOBJVertexCoordinates();

		/**
		 Reads a set of vertex normal coordinates.

		 @pre			All the vertex normals in the OBJ file are normalized.
		 @return		The @c Normal3 represented by the next token of this 
						OBJ reader (modified according to the mesh descriptor 
						of this OBj reader).
		 @throws		Exception
						Failed to read a @c Normal3.
		 */
		[[nodiscard]]
		const Normal3 ReadOBJVertexNormalCoordinates();

		/**
		 Reads a set of vertex texture coordinates.

		 @return		The @c UV represented by the next token of this OBJ 
						reader (modified according to the mesh descriptor of 
						this OBj reader).
		 @throws		Exception
						Failed to read a @c UV.
		 */
		[[nodiscard]]
		const UV ReadOBJVertexTextureCoordinates();

		/**
		 Reads a set of face indices.

		 @return		The face indices represented by the next token of this 
						OBJ reader.	A zero indicates the absence of a 
						component.
		 @throws		Exception
						Failed to read a Bool variable.
		 */
		[[nodiscard]]
		const Index3 ReadOBJVertexIndices();
		
		/**
		 Constructs or retrieves (if already existing) the vertex matching the 
		 given vertex indices.

		 @param[in]		vertex_indices
						A reference to the vertex indices.
		 @return		The vertex matching the given vertex indices 
						@a vertex_indices.
		 */
		[[nodiscard]]
		const VertexT ConstructVertex(const Index3& vertex_indices);

		/**
		 A struct of @c Index3 comparators for OBJ vertex indices.
		 */
		struct OBJComparatorIndex3 final {

		public:

			/**
			 Compares the two given @c Index3 vectors against each other.

			 @param[in]		lhs
							A reference to the first vector.
			 @param[in]		rhs
							A reference to the second vector.
			 @return		@c true if the @a lhs is smaller than @a rhs. 
							@c false otherwise.
			 */
			[[nodiscard]]
			bool operator()(const Index3& lhs, const Index3& rhs) const noexcept {

				return (lhs.m_x == rhs.m_x) ? ((lhs.m_y == rhs.m_y) ? (lhs.m_z < rhs.m_z) 
					                                                : (lhs.m_y < rhs.m_y)) 
					                        : (lhs.m_x < rhs.m_x);
			}
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector containing the read vertex position coordinates of this OBJ 
		 reader.
		 */
		std::vector< Point3 >  m_vertex_coordinates;

		/**
		 A vector containing the read vertex texture coordinates of this OBJ 
		 reader.
		 */
		std::vector< UV > m_vertex_texture_coordinates;

		/**
		 A vector containing the read normal texture coordinates of this OBJ 
		 reader.
		 */
		std::vector< Normal3 > m_vertex_normal_coordinates;

		/**
		 A mapping between vertex position/texture/normal coordinates' indices
		 and the index of a vertex in the vertex buffer (@c m_model_output) of 
		 this OBJ reader.
		 */
		std::map< Index3, IndexT, OBJComparatorIndex3 > m_mapping;
		
		/**
		 A reference to the resource manager of this OBJ reader.
		 */
		ResourceManager& m_resource_manager;

		/**
		 A reference to a model output containing the read data of this OBJ 
		 reader.
		 */
		ModelOutput< VertexT, IndexT >& m_model_output;

		/**
		 A reference to the mesh descriptor for this OBJ reader.
		 */
		const MeshDescriptor< VertexT, IndexT >& m_mesh_desc;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_reader.tpp"

#pragma endregion