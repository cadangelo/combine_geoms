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
moab::Tag tag_num;
// Geometric Categories
const char geom_category[][CATEGORY_TAG_SIZE] =
                  { "Vertex\0","Curve\0","Surface\0","Volume\0","Group\0"};

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

std::string map_tag_to_mat(int tag_number)  
{
  std::map<int, std::string> tag_map;
  std::string mat_name;

  tag_map[1]="mat:Subcutaneous_Fat";
  tag_map[2]="mat:Subcutaneous_Fat";
  tag_map[3]="mat:Subcutaneous_Fat";
  tag_map[4]="mat:Muscle";
  tag_map[5]="mat:Muscle";
  tag_map[6]="mat:Muscle";
  tag_map[7]="mat:Visceral_Fat";
  tag_map[8]="mat:Blood";
  tag_map[9]="mat:Blood";
  tag_map[10]="mat:Blood";
  tag_map[11]="mat:Blood";
  tag_map[12]="mat:Blood";
  tag_map[13]="mat:Blood";
  tag_map[14]="mat:Skin";
  tag_map[15]="mat:Air";
  tag_map[16]="mat:Water";
  tag_map[17]="mat:Carbon";
  tag_map[21]="mat:Brain";
  tag_map[22]="mat:Nasal_Layer";
  tag_map[23]="mat:Nasal_Layer";
  tag_map[24]="mat:Eye";
  tag_map[25]="mat:Lens";
  tag_map[26]="mat:Lens";
  tag_map[27]="mat:External_Nose";
  tag_map[28]="mat:Ears";
  tag_map[29]="mat:Pituitary_Gland";
  tag_map[30]="mat:Salivary_Glands";
  tag_map[31]="mat:Salivary_Glands";
  tag_map[32]="mat:Salivary_Glands";
  tag_map[33]="mat:Oral_Cavity_Layer";
  tag_map[34]="mat:Tongue";
  tag_map[35]="mat:Tonsils";
  tag_map[36]="mat:Pharynx";
  tag_map[37]="mat:Spinal_Cord";
  tag_map[38]="mat:Larynx";
  tag_map[39]="mat:Thyroid";
  tag_map[40]="mat:Esophagus";
  tag_map[41]="mat:Thymus";
  tag_map[42]="mat:Lung";
  tag_map[43]="mat:Lung";
  tag_map[44]="mat:Trachea";
  tag_map[45]="mat:Trachea";
  tag_map[46]="mat:Breast_Fat_M";
  tag_map[47]="mat:Breast_Fat_M";
  tag_map[50]="mat:Breast_Glandular_M";
  tag_map[51]="mat:Breast_Glandular_M";
  tag_map[52]="mat:Heart";
  tag_map[53]="mat:Blood";
  tag_map[54]="mat:Liver";
  tag_map[55]="mat:Stomach";
  tag_map[56]="mat:Water";
  tag_map[57]="mat:Spleen";
  tag_map[58]="mat:Gall_Bladder_Wall";
  tag_map[59]="mat:Water";
  tag_map[60]="mat:Adrenals";
  tag_map[61]="mat:Adrenals";
  tag_map[62]="mat:Kidney";
  tag_map[63]="mat:Kidney";
  tag_map[64]="mat:Kidney";
  tag_map[65]="mat:Kidney";
  tag_map[66]="mat:Kidney";
  tag_map[67]="mat:Kidney";
  tag_map[68]="mat:Small_Intestine";
  tag_map[69]="mat:Water";
  tag_map[70]="mat:Pancreas";
  tag_map[71]="mat:Large_Intestine";
  tag_map[72]="mat:Water";
  tag_map[73]="mat:Large_Intestine";
  tag_map[74]="mat:Water";
  tag_map[75]="mat:Large_Intestine";
  tag_map[76]="mat:Water";
  tag_map[77]="mat:Urinary";
  tag_map[78]="mat:Water";
  tag_map[79]="mat:Uterus";
  tag_map[80]="mat:Ovaries";
  tag_map[81]="mat:Prostate";
  tag_map[82]="mat:Penis";
  tag_map[83]="mat:Scrotum";
  tag_map[84]="mat:Testes";
  tag_map[100]="mat:Air";
  tag_map[101]="mat:Cartilage";
  tag_map[102]="mat:Cartilage";
  tag_map[103]="mat:Cartilage";
  tag_map[104]="mat:Cartilage";
  tag_map[105]="mat:Cartilage";
  tag_map[106]="mat:Cartilage";
  tag_map[107]="mat:Cartilage";
  tag_map[108]="mat:Cartilage";
  tag_map[109]="mat:Cartilage";
  tag_map[110]="mat:Cartilage";
  tag_map[111]="mat:Cartilage";
  tag_map[112]="mat:Cartilage";
  tag_map[113]="mat:Cartilage";
  tag_map[114]="mat:Cartilage";
  tag_map[115]="mat:Cartilage";
  tag_map[116]="mat:Cartilage";
  tag_map[117]="mat:Cartilage";
  tag_map[118]="mat:Cartilage";
  tag_map[119]="mat:Cartilage";
  tag_map[120]="mat:Cartilage";
  tag_map[121]="mat:Cartilage";
  tag_map[122]="mat:Cartilage";
  tag_map[123]="mat:Cartilage";
  tag_map[124]="mat:Cartilage";
  tag_map[125]="mat:Cartilage";
  tag_map[126]="mat:Cartilage";
  tag_map[127]="mat:Cartilage";
  tag_map[128]="mat:Cartilage";
  tag_map[129]="mat:Cartilage";
  tag_map[130]="mat:Cartilage";
  tag_map[131]="mat:Cartilage";
  tag_map[133]="mat:Lymph_Nodes";
  tag_map[134]="mat:Lymph_Nodes";
  tag_map[135]="mat:Lymph_Nodes";
  tag_map[136]="mat:Lymph_Nodes";
  tag_map[137]="mat:Lymph_Nodes";
  tag_map[138]="mat:Lymph_Nodes";
  tag_map[139]="mat:Lymph_Nodes";
  tag_map[140]="mat:Lymph_Nodes";
  tag_map[141]="mat:Lymph_Nodes";
  tag_map[142]="mat:Lymph_Nodes";
  tag_map[143]="mat:Lymph_Nodes";
  tag_map[144]="mat:Lymph_Nodes";
  tag_map[145]="mat:Lymph_Nodes";
  tag_map[146]="mat:Lymph_Nodes";
  tag_map[147]="mat:Lymph_Nodes";
  tag_map[148]="mat:Lymph_Nodes";
  tag_map[151]="mat:Cortical_bone";
  tag_map[152]="mat:Cortical_bone";
  tag_map[153]="mat:Cortical_bone";
  tag_map[154]="mat:Cortical_bone";
  tag_map[155]="mat:Cortical_bone";
  tag_map[156]="mat:Cortical_bone";
  tag_map[157]="mat:Cortical_bone";
  tag_map[158]="mat:Cortical_bone";
  tag_map[159]="mat:Cortical_bone";
  tag_map[160]="mat:Cortical_bone";
  tag_map[161]="mat:Cortical_bone";
  tag_map[162]="mat:Cortical_bone";
  tag_map[163]="mat:Cortical_bone";
  tag_map[164]="mat:Cortical_bone";
  tag_map[165]="mat:Cortical_bone";
  tag_map[166]="mat:Cortical_bone";
  tag_map[167]="mat:Cortical_bone";
  tag_map[168]="mat:Cortical_bone";
  tag_map[169]="mat:Cortical_bone";
  tag_map[170]="mat:Cortical_bone";
  tag_map[171]="mat:Cortical_bone";
  tag_map[172]="mat:Cortical_bone";
  tag_map[173]="mat:Cortical_bone";
  tag_map[174]="mat:Cortical_bone";
  tag_map[175]="mat:Cortical_bone";
  tag_map[176]="mat:Cortical_bone";
  tag_map[177]="mat:Cortical_bone";
  tag_map[178]="mat:Cortical_bone";
  tag_map[179]="mat:Cortical_bone";
  tag_map[180]="mat:Cortical_bone";
  tag_map[181]="mat:Cortical_bone";
  tag_map[182]="mat:Cortical_bone";
  tag_map[183]="mat:Cortical_bone";
  tag_map[184]="mat:Cortical_bone";
  tag_map[185]="mat:Teeth";
  tag_map[201]="mat:spmc_Cranium";
  tag_map[202]="mat:spmc_Mandible";
  tag_map[203]="mat:spmc_Scapulae";
  tag_map[204]="mat:spmc_Clavicles";
  tag_map[205]="mat:spmc_Sternum";
  tag_map[206]="mat:spmc_Ribs";
  tag_map[207]="mat:spmc_Vertebrae_C";
  tag_map[208]="mat:spmc_Vertebrae_T";
  tag_map[209]="mat:spmc_Vertebrae_L";
  tag_map[210]="mat:spmc_Sacrum";
  tag_map[211]="mat:spmc_Os_Coxae";
  tag_map[212]="mat:spmc_Femora_proximal";
  tag_map[213]="mat:spmc_Femora_upper_shaft";
  tag_map[214]="mat:spmc_Femora_lower_shaft";
  tag_map[215]="mat:spmc_Femora_distal";
  tag_map[216]="mat:spmc_Tibiae_proximal";
  tag_map[217]="mat:spmc_Tibiae_shaft";
  tag_map[218]="mat:spmc_Tibiae_distal";
  tag_map[219]="mat:spmc_Fibulae_proximal";
  tag_map[220]="mat:spmc_Fibulae_shaft";
  tag_map[221]="mat:spmc_Fibulae_distal";
  tag_map[222]="mat:spmc_Patellae";
  tag_map[223]="mat:spmc_Ankles_and_feet";
  tag_map[224]="mat:spmc_Humera_proximal";
  tag_map[225]="mat:spmc_Humera_upper_shaft";
  tag_map[226]="mat:spmc_Humera_lower_shaft";
  tag_map[227]="mat:spmc_Humera_distal";
  tag_map[228]="mat:spmc_Radii_proximal";
  tag_map[229]="mat:spmc_Radii_shaft";
  tag_map[230]="mat:spmc_Radii_distal";
  tag_map[231]="mat:spmc_Ulnae_proximal";
  tag_map[232]="mat:spmc_Ulnae_shaft";
  tag_map[233]="mat:spmc_Ulnae_distal";
  tag_map[234]="mat:spmc_Wrists_and_hands";
  

//  std::cout << tag_map.find(tag_number)->second << std::endl;
  mat_name = tag_map.find(tag_number)->second;
  
  return mat_name;
}

int main(int argc, char* argv[]) {

  moab::ErrorCode rval;
  moab::Core *mbi = new moab::Core();
  
  std::string output_file = "new.h5m";

  get_all_handles(mbi);
  
  rval = mbi->load_file("phantom_in_hab.h5m");
//  rval = mbi->load_file("big_graveyard.h5m");

  moab::Range::iterator it;
  int id_num = 1;// ent_sets.size();
  int num;
  std::string material_name;
  moab::Range ent_sets, grave_set;
  
  rval =  mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &tag_num, NULL, 1, ent_sets);
  CHECK_ERR(rval);
  //std::cout<< ent_sets.size() << std::endl;
      moab::Tag tag_arr[1] = {category_tag};
      const char *dum = geom_category[4];
      const void *const ptr[1] = {dum};
   
  //rval =  mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &tag_arr[0], ptr, 1, grave_set);
  //CHECK_ERR(rval);
//  rval =  mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &category_tag, NULL, 1, grave_set);
 // CHECK_ERR(rval);
 
  std::string grave_name;
  grave_name = "mat:Graveyard";
  grave_name.resize (32); 
  //rval = mbi->tag_set_data(name_tag, &(*grave_set.begin()), 1, grave_name.c_str());

  moab::EntityHandle material_set;

  int mat_id = 0;

  for (it = ent_sets.begin(); it != ent_sets.end(); ++it) 
    {
      rval = mbi->tag_get_data(tag_num, &(*it), 1, &num);
      CHECK_ERR(rval);

      material_name = map_tag_to_mat(num);   
      material_name.resize (32);
      //std::cout << material_name << std::endl; 

      rval = mbi->tag_get_handle(NAME_TAG_NAME, 32, moab::MB_TYPE_OPAQUE, name_tag);
      //moab::Range sets_w_names;
      //rval = mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &name_tag, NULL, 1, sets_w_names);
      
      moab::Tag tag_arr[1] = {name_tag};
      const char *dum = material_name.c_str();
      const void *const ptr[1] = {dum};
      moab::Range mats;
      rval = mbi->get_entities_by_type_and_tag(0, moab::MBENTITYSET, &tag_arr[0], ptr, 1, mats);

    

      if (mats.size() == 0 ) 
        {

           rval = mbi->create_meshset( moab::MESHSET_SET, material_set);
           CHECK_ERR(rval);

           mat_id++;
           rval = mbi->tag_set_data( geom_tag, &material_set, 1, &geom_category[4]);
       
           rval = mbi->tag_set_data( id_tag, &material_set, 1, &(mat_id));
        
           rval = mbi->tag_set_data( name_tag, &material_set, 1, material_name.c_str());
        
           rval = mbi->tag_set_data( category_tag, &material_set, 1,
                                     geom_category[4]);
 
        }
      else
        {
          material_set = *mats.begin();
        }
 
      rval = mbi->add_entities(material_set, &(*it), 1);

    }
    //  char matname[32];
    //  rval = mbi->tag_get_data(name_tag, &(material_set), 1, &matname);
    //  CHECK_ERR(rval);
  //    std::cout << matname << std::endl;
  
  // save file
  rval = mbi->write_mesh(output_file.c_str());
  

  return 0;
}    
