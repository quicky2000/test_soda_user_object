/*
    This file is part of test_soda_user_object
    Copyright (C) 2012  Julien Thevenon ( julien_thevenon at yahoo.fr )

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "user_object_analyzer.h"
#include "module_configuration.h"

int main(void)
{
  osm_diff_analyzer_if::module_configuration l_conf("toto","type");
  l_conf.add_parameter("user_name","quicky");
  osm_diff_analyzer_user_object::user_object_analyzer l_analyzer(&l_conf,
                                                                 (osm_diff_analyzer_user_object::user_object_common_api*)10
                                                                 );
  std::vector<osm_api_data_types::osm_change*> l_changes;

  osm_api_data_types::osm_node * l_node123_v1 = new osm_api_data_types::osm_node(123,12.34,56.78,"aujourdhui",1,666,0xDAD,"dad");
  osm_api_data_types::osm_node * l_node456_v1 = new osm_api_data_types::osm_node(456,34.12,78.56,"aujourdhui",1,666,0xDAD,"dad");

  osm_api_data_types::osm_way * l_way = new osm_api_data_types::osm_way(10,"2012-10-25",1,680,0xDEAD,"quicky");
  l_way->add_node(l_node123_v1->get_id());
  l_way->add_node(l_node456_v1->get_id());

  osm_api_data_types::osm_node * l_node123_v2 = new osm_api_data_types::osm_node(123,12.34,56.78,"apres",2,700,0xBEEF,"toto");


  osm_api_data_types::osm_change * l_create_node123_v1 = new osm_api_data_types::osm_change_generic<osm_api_data_types::osm_node>(osm_api_data_types::osm_change::CREATION,l_node123_v1);
  osm_api_data_types::osm_change * l_create_node456_v1 = new osm_api_data_types::osm_change_generic<osm_api_data_types::osm_node>(osm_api_data_types::osm_change::CREATION,l_node456_v1);
  osm_api_data_types::osm_change * l_create_way = new osm_api_data_types::osm_change_generic<osm_api_data_types::osm_way>(osm_api_data_types::osm_change::CREATION,l_way);
  l_changes.push_back(l_create_node123_v1);
  l_changes.push_back(l_create_node456_v1);
  l_changes.push_back(l_create_way);

  l_analyzer.analyze(l_changes);
  l_changes.clear();

  delete l_create_way;
  delete l_create_node456_v1;
  delete l_create_node123_v1;

  osm_api_data_types::osm_change * l_change_modify = new osm_api_data_types::osm_change_generic<osm_api_data_types::osm_node>(osm_api_data_types::osm_change::MODIFICATION,l_node123_v2);
  l_changes.push_back(l_change_modify);
  l_analyzer.analyze(l_changes);
  l_changes.clear();

  delete l_change_modify;
}
