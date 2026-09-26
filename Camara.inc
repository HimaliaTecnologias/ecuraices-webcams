<?php

require('/var/www/vhosts/webcamsdeasturias.com/httpdocs/dao/Camara_DAO.inc');

class Camara
{
  public function __construct() {
  }
    
  function getTotalCams(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getTotalCams();
  }

  function getCamsInstaladas(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getCamsInstaladas();
  }

  function getCamsEnInstalacion(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getCamsEnInstalacion();
  }

  function getCamsHD(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getCamsHD();
  }

  function getCamsMantenimiento(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getCamsMantenimiento();
  }

  function getCamsMejora(){
    $camara_dao=new Camara_DAO();
    return $camara_dao->getCamsMejora();
  }

  function getListaCamaras() {
     $camara_dao=new Camara_DAO();
      $lista=$camara_dao->getListaCamaras();
      return $lista;
  }
  
 function getListaCamarasConcejo($id) {
  	  $camara_dao=new Camara_DAO();
      $lista=$camara_dao->getListaCamarasConcejo($id);
      return $lista;
  }
  
  function getListaCamarasCercanas($id) {
  	  $camara_dao=new Camara_DAO();
      $lista=$camara_dao->getListaCamarasCercanas($id);
      return $lista;
  }
  
  function getListaCamarasCategoria($id) {
  	  $camara_dao=new Camara_DAO();
      $lista=$camara_dao->getListaCamarasCategoria($id);
      return $lista;
  }

  function getListaCamarasUsuario($id) {
  	  $camara_dao=new Camara_DAO();
      $lista=$camara_dao->getListaCamarasUsuario($id);
      return $lista;
  }
 
  function getCamara($id){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->getCamara($id);
      return $aux;
  }
  
  function getNovedad(){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->getNovedad();
      return $aux;
  }
  
  function getVotada(){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->getVotada();
      return $aux;
  }

  function setVotada($id,$puntos){
  	  $camara_dao=new Camara_DAO();
      $camara_dao->setVotada($id,$puntos);
  }

  function addFavorita($idUsuario,$idCamara){
  	  $camara_dao=new Camara_DAO();
      $camara_dao->addFavorita($idUsuario,$idCamara);
  }

  function removeFavorita($idUsuario,$idCamara){
  	  $camara_dao=new Camara_DAO();
      $camara_dao->removeFavorita($idUsuario,$idCamara);
  }

 function isFavorita($idUsuario,$idCamara){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->isFavorita($idUsuario,$idCamara);
return $aux;
  }
  
  function getDeldia(){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->getDeldia();
      return $aux;
  }
  
  function setVisitas($id){
  	 $camara_dao=new Camara_DAO();
     $camara_dao->setVisitas($id);
  }
  
  function getTags(){
  	  $camara_dao=new Camara_DAO();
      $aux=$camara_dao->getTags();
      return $aux;
  }

  function getUrlFriendly($id){

		switch($id){
			case 1: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/llastres/puerto-muelle-de-lastres-hd/1/'; break; 
			case 2: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/cangas-de-onis/cangas-de-onis-desde-contranquil/2/'; break; 
			case 3: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/langreo/sama-de-langreo/plaza-de-espana/3/'; break; 
			case 4: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/lastres/mirador-de-san-roque-de-lastres-hd/4/'; break; 
			case 5: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/cudillero/cudillero/anfiteatro-de-cudillero/5/'; break; 
			case 6: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-aviles/aviles/aviles/ria-de-aviles-hd/6/'; break; 
			case 7: return 'http://www.webcamsdeasturias.com/asturias/estacion-valgrande-pajares/lena/pajares/ei-valgrande-pajares-valle-del-sol-1700-metros-hd/7/'; break; 
			case 8: return 'http://www.webcamsdeasturias.com/asturias/oriente/penamellera-baja/panes/plaza-nueva-de-panes/8/'; break; 
			case 9: return 'http://www.webcamsdeasturias.com/asturias/estacion-valgrande-pajares/lena/pajares/ei-valgrande-pajares-cuitu-negro-cueto-negro-hd/9/'; break; 
			case 10: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/nava/nava/plaza-de-manuel-uria-nava-hd/10/'; break; 
			case 11: return 'http://www.webcamsdeasturias.com/asturias/oriente/parres/arriondas/panoramica-de-arriondas/11/'; break; 
			case 12: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/huerres/picu-pienzu-sierra-del-sueve/12/'; break; 
			case 13: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/villanueva-de-oscos/villanueva-de-oscos/villanueva-de-oscos-hd/13/'; break; 
			case 14: return 'http://www.webcamsdeasturias.com/asturias/centro/llanera/posada-de-llanera/posada-de-llanera/14/'; break; 
			case 15: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/llanes/plaza-parres-sobrino-llanes-hd/15/'; break; 
			case 16: return 'http://www.webcamsdeasturias.com/asturias/oriente-de-asturias/llanes/barro/playa-de-barro-hd/16/'; break; 
			case 17: return 'http://www.webcamsdeasturias.com/asturias/occidente/degana/degana/panoramica-degana-desde-ayto-hd/17/'; break; 
			case 18: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/soto-del-barco/san-juan-de-la-arena/playa-los-quebrantos-hd/18/'; break; 
			case 19: return 'http://www.webcamsdeasturias.com/asturias/occidente/tineo/tineo/panoramica-de-tineo/19/'; break; 
			case 20: return 'http://www.webcamsdeasturias.com/asturias/leon/villamanin/villamanin/panoramica-plaza-villamanin/20/'; break; 
			case 21: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/margolles/panoramica-margolles-hd/21/'; break; 
			case 22: return 'http://www.webcamsdeasturias.com/asturias/oriente/cabrales/poncebos/poncebos-ruta-del-cares-hd/22/'; break; 
			case 23: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/carreno/candas/paseo-maritimo-de-candas/23/'; break; 
			case 24: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/gozon/luanco/playa-de-la-ribera-hd/24/'; break; 
			case 25: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/la-guia-playa-de-santa-marina-hd/25/'; break; 
			case 26: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-aviles/castrillon/salinas/playa-de-salinas-hd/26/'; break; 
			case 27: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/castropol/penarronda/playa-de-penarronda-hd/27/'; break; 
			case 28: return 'http://www.webcamsdeasturias.com/asturias/occidente/castropol/figueras/puerto-de-as-figueiras-hd/28/'; break; 
			case 29: return 'http://www.webcamsdeasturias.com/asturias/occidente/coana/ortiguera/playa-de-arnielles-hd/29/'; break; 
			case 30: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/villayon/villayon/villayon-hd/30/'; break; 
			case 31: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/proaza/proaza/proaza-hd/31/'; break; 
			case 32: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/paseo-princesa-letizia-hd/32/'; break; 
			case 33: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/tapia-de-casariego/tapia-de-casariego/puerto-de-tapia-de-casariego-hd/33/'; break; 
			case 34: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/cangas-de-onis/puente-romano-hd/34/'; break; 
			case 35: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/mestas-de-con/mestas-de-con/35/'; break; 
			case 36: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/tapia-de-casariego/tapia-de-casariego/puerto-de-tapia-de-casariego-II-hd/36/'; break; 
			case 37: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/laviana/pola-de-laviana/parque-pola-de-laviana-hd/37/'; break; 
			case 38: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/soto-del-barco/san-juan-del-arena/muelle-de-san-juan-de-la-arena-hd/38/'; break; 
			case 39: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/llanes/puerto-de-llanes-hd/39/'; break; 
			case 40: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/castropol/penarronda/playa-de-penarronda/40/'; break; 
			case 41: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/gijon/puerto-deportivo-poniente-hd/41/'; break; 
			case 42: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/colunga/casco-urbano/42/'; break; 
			case 43: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/camarmena/picu-urriellu-naranjo-de-bulnes-hd/43/'; break; 
			case 44: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/rodiles/surf-barra-de-playa-de-rodiles-hd/44/'; break; 
			case 45: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/grado/grado/parque-de-arriba-parque-manuel-pedregal/45/'; break; 
			case 46: return 'http://www.webcamsdeasturias.com/asturias/occidente/fuentes-del-narcea/cangas-del-narcea/panoramica-cangas-del-narcea-hd/46/'; break; 
			case 47: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/costa-de-caravia-arenal-de-moris-II-hd/47/'; break; 
			case 48: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/teverga/teverga/panoramica-de-teverga/48/'; break; 
			case 49: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/lastres/puerto-de-lastres-hd/49/'; break; 
			case 50: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/tazones/puerto-de-tazones-hd/50/'; break; 
			case 51: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/penamellera-alta/niserias/embalse-de-casa-julian/51/'; break; 
			case 52: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/onis/benia-de-onis/plaza-del-ayto-de-onis/52/'; break; 
			case 53: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/llanes/playa-de-toro-mirador-de-toro-hd/53/'; break; 
			case 54: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/muros-de-nalon/aguilar/playa-de-aguilar-panoramica-hd/54/'; break; 
			case 55: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/colunga/playa-de-la-griega-hd/55/'; break; 
			case 56: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/poo/playa-de-poo-hd/56/'; break; 
			case 57: return 'http://www.webcamsdeasturias.com/asturias/cantabria/san-vicente/san-vicente/panoramica-san-vicente-hd/57/'; break; 
			case 58: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/barro/playa-de-barro/58/'; break; 
			case 59: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/muros-de-nalon/san-esteban-de-pravia/desembocadura-del-rio-nalon-hd/59/'; break; 
			case 60: return 'http://www.webcamsdeasturias.com/asturias/centro/oviedo/oviedo/oviedo-desde-el-naranco/60/'; break; 
			case 61: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/gozon/luanco/vista-panoramica-de-luanco/61/'; break; 
			case 62: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/taramundi/taramundi/taramundi-hd/62/'; break; 
			case 63: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-aviles/aviles/aviles/parque-del-muelle-hd/63/'; break; 
			case 64: return 'http://www.webcamsdeasturias.com/asturias/oviedo/oviedo/oviedo/calle-general-elorza/64/'; break; 
			case 65: return 'http://www.webcamsdeasturias.com/asturias/montana-central/mieres/mieres/mieres-hd/65/'; break; 
			case 66: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/grado/grado/grado-panoramica-desde-el-ayto/66/'; break; 
			case 67: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/navia/navia/playa-de-navia-hd/67/'; break; 
			case 68: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/gijon/iglesia-de-san-pedro-cimadevilla-hd/68/'; break; 
			case 69: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/navia/navia/darsena-de-navia-hd/69/'; break; 
			case 70: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/el-franco/viavelez/viavelez-hd/70/'; break; 
			case 71: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/playa-de-la-espasa-hd/71/'; break; 
			case 72: return 'http://www.webcamsdeasturias.com/asturias/cuenca-minera/langreo/la-felguera/la-felguera/72/'; break; 
			case 73: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/salas/salas/panoramica-de-salas-hd/73/'; break; 
			case 74: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-nalon/laviana/laviana/pola-de-laviana/74/'; break; 
			case 75: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/villaviciosa/villaviciosa-ayuntamiento-plaza-guevu-hd/75/'; break; 
			case 76: return 'http://www.webcamsdeasturias.com/asturias/occidente/degana/panoramica-de-cerredo/cerredo-hd/76/'; break; 
			case 77: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/quiros/quiros/quiros-desde-el-museo-etnografico/77/'; break; 
			case 78: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadedeva/colombres/colombres-iglesia-plaza-y-archivo-de-indianos-hd/78/'; break; 
			case 79: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/arenal-de-moris-hd/79/'; break; 
			case 80: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/covadonga/covadonga/80/'; break; 
			case 81: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/sotres/sotres-pandebano/81/'; break; 
			case 82: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/las-regueras/las-regueras/las-regueras/82/'; break; 
			case 83: return 'http://www.webcamsdeasturias.com/asturias/oriente/parres/arriondas/panoramica-del-rio-sella-hd/83/'; break; 
			case 84: return 'http://www.webcamsdeasturias.com/asturias/fuentes-de-invierno-san-isidro/aller/san-isidro/san-isidro-fuentes-de-invierno/84/'; break; 
			case 85: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/valdeon/cain/cain-ruta-del-cares/85/'; break; 
			case 86: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/quiros/barzana/panoramica-de-barzana-hd/86/'; break; 
			case 87: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/gijon/fomento-poniente/87/'; break; 
			case 88: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-aviles/castrillon/santa-maria-del-mar/playa-de-santa-maria-del-mar/88/'; break; 
			case 89: return 'http://www.webcamsdeasturias.com/asturias/oviedo/buenavista/meteobuenavista/panoramica-oviedo-desde-barrio-buenavista/89/'; break; 
			case 90: return 'http://www.webcamsdeasturias.com/asturias/oriente/ponga/san-juan-de-beleno/san-juan-de-beleno-san-xuan-picu-tiatordos/90/'; break; 
			case 91: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/gozon/luanco/muelle-de-luanco-hd/91/'; break; 
			case 92: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-de-navia/boal/boal/boal-desde-el-ayto-hd/92/'; break; 
			case 93: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/gozon/verdicio/verdicio/93/'; break; 
			case 94: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/la-isla/playa-de-la-isla-hd/94/'; break; 
			case 95: return 'http://www.webcamsdeasturias.com/asturias/cangas-de-onis/cangas-de-onis/cangas-de-onis/refugio-vegarredonda/95/'; break; 
			case 96: return 'http://www.webcamsdeasturias.com/asturias/montana-central/aller/cabanaquinta/cabanaquinta/96/'; break; 
			case 97: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/cudillero/cudillero/plaza-de-la-marina-ayuntamiento/97/'; break; 
			case 98: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/navia/navia/playa-de-frejulfe-hd/98/'; break; 
			case 99: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/caso/campo-de-caso/campo-de-caso-hd/99/'; break; 
			case 100: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/ortiguero/ortiguero/100/'; break; 
			case 101: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/belmonte-de-miranda/belmonte/panoramica-de-belmonte-de-miranda/101/'; break; 
			case 102: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/teverga/teverga/teverga/102/'; break; 
			case 103: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/caso/tanes/embalse-de-tanes-hd/103/'; break; 
			case 104: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/villaviciosa/playa-de-la-nora-hd/104/'; break; 
			case 105: return 'http://www.webcamsdeasturias.com/asturias/montana-central/aller/felechosa/panoramica-san-isidro-felechosa-hd/105/'; break; 
			case 106: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/somiedo/somiedo/somiedo-caunedo-hd/106/'; break; 
			case 107: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/santo-adriano/tunon/tunon-senda-del-oso/107/'; break; 
			case 108: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/grado/grado/grado/108/'; break; 
			case 109: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/belmonte/belmonte/belmonte/109/'; break; 
			case 110: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/yernes-y-tameza/villabre/villabre/110/'; break; 
			case 111: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/puerto-de-ribadesella/111/'; break; 
			case 112: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/santo-adriano/tunon/villanueva-senda-del-oso/112/'; break; 
			case 113: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/somiedo/somiedo/pola-de-somiedo-hd/113/'; break; 
			case 114: return 'http://www.webcamsdeasturias.com/asturias/occidente/tapia-de-casariego/tapia-de-casariego/playa-de-tapia-anguileiro-o-la-grande-hd/114/'; break; 
			case 115: return 'http://www.webcamsdeasturias.com/asturias/occidente/valdes/luarca/acantilados-de-luarca-valdes-hd/115/'; break; 
			case 116: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/bulnes/panoramica-de-bulnes/116/'; break; 
			case 117: return 'http://www.webcamsdeasturias.com/asturias/oriente-de-asturias/ribadedeva/ribadedeva/playa-de-la-franca-hd/117/'; break; 
			case 118: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/gozon/xago/playa-de-xago-hd/118/'; break; 
			case 119: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/tazones/playa-de-tazones-hd/119/'; break; 
			case 120: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/rodiles/playa-de-rodiles-hd/120/'; break; 
			case 121: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/villaviciosa/playa-de-la-nora/121/'; break; 
			case 122: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/muros-de-nalon/aguilar/playa-de-aguilar-hd/122/'; break; 
			case 123: return 'http://www.webcamsdeasturias.com/asturias/estacion-valgrande-pajares/lena/pajares/ei-valgrande-pajares-valle-del-sol-1800-metros-hd/123/'; break; 
			case 124: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/pilona/infiesto/infiesto/124/'; break; 
			case 125: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/barra-de-ribadesella-hd/125/'; break; 
			case 126: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/costa/el-rinconin-san-lorenzo-hd/126/'; break; 
			case 127: return 'http://www.webcamsdeasturias.com/asturias/occidente/navia/puerto-de-vega/puerto-de-vega-hd/127/'; break; 
			case 128: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/cangas-de-onis/lagos-de-covadonga-lago-enol/128/'; break; 
			case 129: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/sotres/panoramica-sotres/129/'; break; 
			case 130: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-nora/siero/pola-de-siero/pola-de-siero/130/'; break; 
			case 131: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/bedon/playa-de-san-antolin-hd/131/'; break; 
			case 132: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/vega/playa-de-vega-hd/132/'; break; 
			case 133: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/gijon/playa-de-san-lorenzo-el-tostaderu-hd/133/'; break; 
			case 135: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/bulnes/refugio-del-urriellu/135/'; break; 
	                case 134: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/el-franco/pormenande/playa-de-pormenande-hd/134/'; break; 
			case 136: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/pravia/somao/panoramica-de-somao-hd/136/'; break; 
			case 137: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/playas-de-el-viso-hd/137/'; break; 
			case 138: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/playa-de-la-espasa-II-hd/138/'; break;  
			case 139: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/san-martin-de-oscos/san-martin-de-oscos/san-martin-de-oscos-hd/139/'; break; 
			case 140: return 'http://www.webcamsdeasturias.com/asturias/occidente/tapia-de-casariego/tapia/playa-la-grande-hd/140/'; break; 
			case 141: return 'http://www.webcamsdeasturias.com/asturias/occidente/tapia-de-casariego/tapia/playa-de-serantes-hd/141/'; break; 
			case 142: return 'http://www.webcamsdeasturias.com/asturias/occidente/grandas-de-salime/grandas-de-salime/grandas-de-salime-hd/142/'; break; 
			case 143: return 'http://www.webcamsdeasturias.com/galicia/marina-lucense/foz/foz/playa-rapadoira-ria-foz/143/'; break; 
			case 144: return 'https://www.webcamsdeasturias.com/asturias/estacion-valgrande-pajares/lena/pajares/ei-valgrande-pajares-panoramica-cueto-negro-ubinas-hd/144/'; break; 
			case 145: return 'http://www.webcamsdeasturias.com/asturias/cabo-penas/carreno/xivares/playa-de-xivares/145/'; break; 
			case 146: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-nora/siero/siero/siero-la-barganiza/146/'; break; 
			case 147: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/caso/tarna/puerto-de-tarna-hd/147/'; break; 
			case 148: return 'http://www.webcamsdeasturias.com/asturias/centro/gijon/gijon/la-escalerona-playa-de-san-lorenzo-hd/148/'; break; 
			case 149: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/soto-del-barco/san-juan-del-arena/playa-de-los-quebrantos-hd/149/'; break; 
			case 150: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/sobrescobio/soto-de-agues/soto-de-agues-ruta-del-alba-hd/150/'; break; 
			case 151: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/cudillero/lamuno/playa-de-la-concha-de-artedo/151/'; break; 
			case 152: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/sobrescobio/rioseco/rioseco-desde-el-ayto/152/'; break; 
			case 153: return 'http://www.webcamsdeasturias.com/asturias/castropol/oscos-eo/castropol/castropol-desde-ribadeo/153/'; break; 
			case 154: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/nava/paraes/paraes-pena-mayor/154/'; break; 
			case 155: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/celoriu/celoriu-playas-las-camaras-y-la-palombina-hd/155/'; break; 
			case 156: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/celorio/playa-palombina-hd/156/'; break; 
			case 157: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/santa-eulalia-de-oscos/santa-eulalia-de-oscos/santa-eulalia-de-oscos-hd/157/'; break; 
			case 158: return 'http://www.webcamsdeasturias.com/asturias/autopista-del-huerna/pola-de-lena/campomanes/webcam-autopista-huerna/158/'; break; 
			case 159: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/cangas-de-onis/lagos-de-covadonga-lago-enol-hd/159/'; break; 
			case 160: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/sotres/sotres-queseria-main-hd/160/'; break; 
			case 161: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/soto-del-barco/san-esteban-de-pravia/bocana-de-san-esteban-de-pravia-hd/161/'; break; 
			case 162: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/amieva/precendi/panoramica-amieva-hd/162/'; break; 
			case 163: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/ibias/ibias/playa-del-ayuntamiento/163/'; break; 
			case 164: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/quintes/playa-espana-hd/164/'; break; 
			case 165: return 'http://www.webcamsdeasturias.com/asturias/estacion-valgrande-pajares/lena/pajares/ei-valgrande-pajares-taquillas-hd/165/'; break; 
			case 166: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/playa-de-santa-marina-hd/166/'; break; 
			case 167: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/san-martin-del-rey-aurelio/sotrondio/sotrondio/167/'; break; 
			case 168: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/lastres/playa-de-la-griega/168/'; break; 
			case 169: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/playas-de-la-espasa-y-la-isla/169/'; break; 
			case 170: return 'http://www.webcamsdeasturias.com/asturias/comarca-aviles/castrillon/salinas/playa-de-salinas-el-espartal/170/'; break; 
			case 171: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/el-franco/porcia/playa-de-porcia-tapia-hd/171/'; break;
			case 172: return 'http://www.webcamsdeasturias.com/asturias/picos-de-europa/cabrales/arenas-de-cabrales/arenas-de-cabrales/172/'; break; 
			case 173: return 'http://www.webcamsdeasturias.com/asturias/camin-real-de-la-mesa/proaza/proacina/pena-de-caranga-escuela-de-escalada-de-quiros/173/'; break; 
		        case 174: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/muros-de-nalon/san-esteban-de-pravia/san-esteban-de-pravia-hd/174/'; break; 
   			case 175: return 'http://www.webcamsdeasturias.com/asturias/bajo-nalon/muros-de-nalon/muros-de-nalon/panoramica-muros-hd/175/'; break; 
			case 176: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/mirador/mirador-del-sella-ribadesella-hd/176/'; break; 
			case 177: return 'http://www.webcamsdeasturias.com/asturias/oriente/cangas-de-onis/vega-de-ario/refugio-marques-villaviciosa-vega-ario/177/'; break; 
			case 178: return 'http://www.webcamsdeasturias.com/asturias/oviedo/naranco/hotel-angel/panoramica-naranco-hd/178/'; break; 
			case 179: return 'http://www.webcamsdeasturias.com/asturias/valle-del-nalon/caso/branagallones/refugio-de-branagallones/179/'; break; 
			case 180: return 'http://www.webcamsdeasturias.com/asturias/montana-central/lena/estacion-valgrande-pajares/zona-baja-hd/180/'; break; 
			case 181: return 'http://www.webcamsdeasturias.com/asturias/comarca-aviles/aviles/plaza-centro-niemeyer/niemeyer-hd/181/'; break; 
	                case 182: return 'http://www.webcamsdeasturias.com/asturias/parque-historico-del-navia/el-franco/porcia/playa-de-porcia-hd/182/'; break;
			case 183: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/colunga/lastres/playa-escanu-lastres-hd/183/'; break; 
			case 184: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/cudillero/cudillero/puerto-de-cudillero-hd/184/'; break; 
			case 185: return 'http://www.webcamsdeasturias.com/asturias/oscos-eo/vegadeo/vegadeo/vegadeo-a-veiga-hd/185/'; break; 
			case 186: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/villaviciosa/playa-de-rodiles/rodiles-hd/186/'; break; 
			case 187: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/andrin/playa-de-andrin-hd/187/'; break; 
			case 188: return 'http://www.webcamsdeasturias.com/asturias/comarca-del-sueve/caravia/caravia/playa-arenal-de-moris-hd/188/'; break; 
			case 189: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/mirador-san-pedro/playa-del-sablon-hd/189/'; break; 
			case 190: return 'http://www.webcamsdeasturias.com/asturias/occidente/valdes/cadavedo/playa-de-cadavedo-hd/190/'; break; 
			case 191: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/nava/panoramica-comarca/nava-cabranes-bimenes-hd/191/'; break; 
			case 192: return 'http://www.webcamsdeasturias.com/asturias/comarca-de-la-sidra/nava/lespraeres/sierra-penamayor-hd/192/'; break; 
			case 193: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/valdes/luarca/panoramica-puerto-luarca-hd/193/'; break; 
			case 194: return 'http://www.webcamsdeasturias.com/asturias/oriente/ribadesella/ribadesella/ria-de-ribadesella-hd/194/'; break; 
			case 195: return 'http://www.webcamsdeasturias.com/asturias/montana-central/lena/estacion-valgrande-pajares/panoramica-estacion-hd/195/'; break; 
			case 196: return 'http://www.webcamsdeasturias.com/asturias/comarca-vaqueira/tineo/tineo/plaza-ayuntamiento-tineo-hd/196/'; break; 
			case 197: return 'http://www.webcamsdeasturias.com/asturias/bajo-deva/ribadedeva/bustio/panoramica-unquera-bustio-hd/197/'; break; 
  	  		case 198: return 'http://www.webcamsdeasturias.com/asturias/gijon/gijon/san-lorenzo/panoramica-playa-hd/198/'; break; 
      			case 199: return 'http://www.webcamsdeasturias.com/asturias/gijon/gijon/estano/playa-estano-hd/199/'; break; 
                        case 200: return 'http://www.webcamsdeasturias.com/asturias/proaza/valles-del-oso/proaza/panoramica-hd/200/'; break; 
			case 201: return 'http://www.webcamsdeasturias.com/asturias/oriente/llanes/el-sablon/los-cubos-de-la-memoria-hd/201/'; break; 
			case 202: return 'http://www.webcamsdeasturias.com/asturias/occidente/coana/parque-historico-navia/muelle-de-ortiguera-hd/202/'; break; 
                        case 203: return 'http://www.webcamsdeasturias.com/asturias/montana-central/aller/san-isidro/la-raya-hd/203/'; break;    
		}
  }

}

?>
