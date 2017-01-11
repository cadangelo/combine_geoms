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
moab::Tag dim_tag;
moab::Tag id_tag;
moab::Tag tag_num;

moab::ErrorCode get_all_handles(moab::Core *mbi)
{
  moab::ErrorCode rval;

  rval = mbi->tag_get_handle( NAME_TAG_NAME, NAME_TAG_SIZE, moab::MB_TYPE_OPAQUE,
			      name_tag, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
  CHECK_ERR(rval);

  rval = mbi->tag_get_handle( "OBJECT_NAME", 32, moab::MB_TYPE_OPAQUE,
			      obj_name_tag, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
  CHECK_ERR(rval);

  rval = mbi->tag_get_handle( "TAG_NUMBER", 1, moab::MB_TYPE_INTEGER,
                              tag_num, moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
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
  
  moab::ErrorCode rval;

  std::string output_file = "combined.h5m";

  get_all_handles(mbi);

  // load all geometry files given in command line args  
  for ( int i = 1 ; i < argc ; ++i ) 
    {
      std::string filename = argv[i];
      std::cout << filename << std::endl;
      rval = mbi->load_file(filename.c_str());
    }

  moab::Range::iterator it;
  int id = 1;
  int dim;
  moab::Range geom_sets;
  
  // get all entities with geom tag
  rval =  mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &geom_tag, NULL, 1, geom_sets);
  CHECK_ERR(rval);

  for (it = geom_sets.begin(); it != geom_sets.end(); ++it) 
    {
      rval = mbi->tag_get_data(geom_tag, &(*it), 1, &dim);
      CHECK_ERR(rval);

      // if set is a surface, volume, or category, renumber it  
      if (dim == 2 || 3 || 4) 
        {
           rval = mbi->tag_set_data(id_tag, &(*it), 1, &(id));
           CHECK_ERR(rval);
           ++id;
        }
    }
  
  // save file
  rval = mbi->write_mesh(output_file.c_str());
 
  return 0;
}    
