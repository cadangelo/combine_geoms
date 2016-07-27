#include <iostream>
#include "moab/Core.hpp"
#include "moab/Interface.hpp"
#include "moab/Types.hpp"
#include "MBTagConventions.hpp"
#include <string>

#define CHECK_ERR(A) do { if (moab::MB_SUCCESS != (A)) {		     \
  std::cerr << "Failure (error code " << (A) << ") at " __FILE__ ":" \
  << __LINE__ << std::endl; \
  return A; } } while(false)

moab::Tag category_tag;
moab::Tag geom_tag;
moab::Tag name_tag;
moab::Tag obj_name_tag;
moab::Tag dim_tag, id_tag;

moab::ErrorCode get_all_handles(moab::Core *mbi)
{
  moab::ErrorCode rval;

  rval = mbi->tag_get_handle( NAME_TAG_NAME, NAME_TAG_SIZE, moab::MB_TYPE_OPAQUE,
			      name_tag, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
  CHECK_ERR(rval);

  rval = mbi->tag_get_handle( "OBJECT_NAME", 32, moab::MB_TYPE_OPAQUE,
			      obj_name_tag, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
  CHECK_ERR(rval);

  int negone = -1;
  rval = mbi->tag_get_handle( GEOM_DIMENSION_TAG_NAME, 1, moab::MB_TYPE_INTEGER,
			      geom_tag, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT,&negone);
  CHECK_ERR(rval);

  rval = mbi->tag_get_handle( GLOBAL_ID_TAG_NAME,
			      1, moab::MB_TYPE_INTEGER,
			      id_tag,
			      moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
  CHECK_ERR(rval);
  
  rval = mbi->tag_get_handle( CATEGORY_TAG_NAME,
			      CATEGORY_TAG_SIZE,
			      moab::MB_TYPE_OPAQUE,
			      category_tag,
			      moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT );

  CHECK_ERR(rval);
  return moab::MB_SUCCESS;
}
  
int main(int argc, char* argv[]) {

  moab::Core *mbi = new moab::Core();
  
  std::string output_file = "hls.h5m";

  get_all_handles(mbi);
  
  int num_files = 5;
  int file_num[num_files] = {14,42,43,52,53};
  moab::ErrorCode rval;
  std::string tagname = "fn_tag_";
  for ( int i = 0 ; i < num_files ; i++ ) {
    std::string filename = tagname+std::to_string(file_num[i])+".obj";
    rval = mbi->load_file(filename.c_str());
  }
  rval = mbi->load_file("big_graveyard.h5m");
  
  moab::Range::iterator it;
  int id_num = 1;// ent_sets.size();
  int dim;
  moab::Range parents;
  moab::Range ent_sets;
  
  rval =  mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &geom_tag, NULL, 1, ent_sets);
  CHECK_ERR(rval);
  for (it = ent_sets.begin(); it != ent_sets.end(); ++it) {
    rval = mbi->tag_get_data(geom_tag, &(*it), 1, &dim);
    CHECK_ERR(rval);
    if (dim == 2) {
      rval = mbi->tag_set_data(id_tag, &(*it), 1, &(id_num));
      CHECK_ERR(rval);
      parents.clear();
      rval = mbi->get_parent_meshsets(*it, parents);
      CHECK_ERR(rval);
      rval = mbi->tag_set_data(id_tag, &(*parents.begin()), 1, &(id_num));
      CHECK_ERR(rval);
      ++id_num;
    }
  }
  
  
  // save file
  rval = mbi->write_mesh(output_file.c_str());
  return 0;
}    
