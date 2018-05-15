#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mdl\mdl_tokens.hpp"
#include "loaders\msh\msh_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >
		::MDLReader(ResourceManager& resource_manager, 
					ModelOutput< VertexT, IndexT >& model_output)
		: LineReader(), 
		m_resource_manager(resource_manager),
		m_model_output(model_output) {}

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >::MDLReader(MDLReader&& reader) noexcept = default;

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >::~MDLReader() = default;

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::Preprocess() {
		using std::empty;
		ThrowIfFailed(empty(m_model_output.m_vertex_buffer), 
					  "%ls: vertex buffer must be empty.", 
					  GetPath().c_str());
		ThrowIfFailed(empty(m_model_output.m_index_buffer), 
					  "%ls: index buffer must be empty.", 
					  GetPath().c_str());

		ImportMesh();
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ImportMesh() {
		auto msh_path = GetPath();
		msh_path.replace_extension(L".msh");

		ImportMSHMeshFromFile(msh_path, m_model_output.m_vertex_buffer,
							            m_model_output.m_index_buffer);
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadLine(NotNull< zstring > line) {
		m_context = nullptr;
		const auto* const token = strtok_s(line, GetDelimiters().c_str(),
										   &m_context);

		if (!token || g_mdl_token_comment == token[0]) {
			return;
		}

		const auto not_null_token = NotNull< const_zstring >(token);

		if (     str_equals(not_null_token, 
							NotNull< const_zstring >(g_mdl_token_submodel))) {

			ReadMDLSubModel();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_mdl_token_material_library))) {

			ReadMDLMaterialLibrary();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetPath().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadMDLSubModel() {
		ModelPart model_part;
		model_part.m_child       = Read< string >();
		model_part.m_parent      = Read< string >();
		model_part.m_transform.SetTranslation(Read< F32, 3 >());
		model_part.m_transform.SetRotation(   Read< F32, 3 >());
		model_part.m_transform.SetScale(      Read< F32, 3 >());
		model_part.m_material    = Read< string >();
		model_part.m_start_index = Read< U32 >();
		model_part.m_nb_indices  = Read< U32 >();
		
		m_model_output.AddModelPart(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadMDLMaterialLibrary() {
		const auto mtl_name = StringToWString(Read< string >());
		auto mtl_path       = GetPath();
		mtl_path.replace_filename(mtl_name);
		
		ImportMaterialFromFile(mtl_path,
							   m_resource_manager, 
							   m_model_output.m_material_buffer);
	}
}