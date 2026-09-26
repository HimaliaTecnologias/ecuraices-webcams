<?php
// Add timezone setting at the very top of the file, before any output
date_default_timezone_set('Europe/Madrid'); 

header('Content-Type: text/html; charset=UTF-8');
ini_set('session.gc_maxlifetime',315360000);
session_set_cookie_params(315360000);
if(!isset($_SESSION)){session_start();}
//session_regenerate_id(TRUE);

require('manager/Usuario.inc');
require('manager/Camara.inc');
require('manager/Concejo.inc'); 
require('manager/Contenido.inc');
require('manager/Comentario.inc');

if(isset($_GET["salir"])){
    session_unset();
    session_destroy();

    unset($_COOKIE['cookie_userId']); 
    setcookie('cookie_userId', null, -1, '/');

    unset($_COOKIE['cookie_nick']); 
    setcookie('cookie_nick', null, -1, '/');

    unset($_COOKIE['cookie_codigo']); 
    setcookie('cookie_codigo', null, -1, '/');

    unset($_COOKIE['cookie_fecha_alta']); 
    setcookie('cookie_fecha_renovacion', null, -1, '/');

    unset($_COOKIE['remember_user']); 
    setcookie('cookie_fecha_renovacion', null, -1, '/');
    
    // Use JavaScript redirect instead of header() since headers may have been sent
    echo "<script>window.location.href = '/';</script>";
    exit();
};

if(isset($_COOKIE["cookie_nick"])) {
    $_SESSION["userId"] = $_COOKIE["cookie_userId"];
    $_SESSION["nick"] = $_COOKIE["cookie_nick"];
    $_SESSION["codigo"] = $_COOKIE["cookie_codigo"];
    $_SESSION["fecha_alta"] = $_COOKIE["cookie_fecha_alta"];
    $_SESSION["fecha_renovacion"] = $_COOKIE["cookie_fecha_renovacion"];
};

$gestion_usuarios=new Usuario();
if(isset($_POST["usuario"])&&(isset($_POST["pass"]))){
   $usuario=$gestion_usuarios->existeUsuario($_POST["usuario"],$_POST["pass"]);
   //echo "usuario ".$usuario->getId()." - ";
   //echo "usuario ".$usuario->getActivo();
    
   if (empty($usuario->getActivo())) {
    session_unset();
    session_destroy();
    $codigo = $usuario->getCodigo();
    if (!isset($codigo) || $codigo == '') {
        $num = rand(100, 999);
        $letra = chr(rand(65, 90));
        $codigo = $num . "-" . $letra;
        $usuario->setCodigo($codigo);
        //$gestion_usuarios->setCodigoUsuario($usuario->getId(), $usuario->getCodigo());
    }
    header("Location: renovacion.php?u=" . $_POST["usuario"] . "&c=" . $codigo);
  }
  
  if ($usuario->getId() < 1) {
    session_unset();
    session_destroy();
    header("Location: error.php");
} else {
    $_SESSION["userId"] = $usuario->getId();
    $_SESSION["nick"] = $_POST["usuario"];
    $_SESSION["codigo"] = $usuario->getCodigo();
    $_SESSION["fecha_alta"] = $usuario->getFechaAlta();
    $_SESSION["fecha_renovacion"] = $usuario->getFechaRenovacion();
    
    setcookie("cookie_userId", $usuario->getId(), time() + (86400 * 30), "/", ".webcamsdeasturias.com"); // 86400 = 1 day
    setcookie("cookie_nick", $_POST["usuario"], time() + (86400 * 30), "/", ".webcamsdeasturias.com");
    setcookie("cookie_codigo", $usuario->getCodigo(), time() + (86400 * 30), "/", ".webcamsdeasturias.com");
    setcookie("cookie_fecha_alta", $usuario->getFechaAlta(), time() + (86400 * 30), "/", ".webcamsdeasturias.com");
    setcookie("cookie_fecha_renovacion", $usuario->getFechaRenovacion(), time() + (86400 * 30), "/", ".webcamsdeasturias.com");
}

}

 $gestion_camaras=new Camara();
 $gestion_usuarios=new Usuario();
 $gestion_contenidos=new Contenido();
 $gestion_comentarios=new Comentario();
 $gestion_concejos=new Concejo();
 
 //Recupero la lista de cámaras
 $lista=$gestion_camaras->getListaCamaras();
 
 //Recupero la cámara novedad
 $novedad=$gestion_camaras->getNovedad();
 
 //Recupero la cámara más votada
 $votada=$gestion_camaras->getVotada();
 
 //Recupero la cámara del día
 $deldia=$gestion_camaras->getDeldia();
 

?>

                                             
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xml:lang="es" lang="es" xmlns="http://www.w3.org/1999/xhtml">
<head>
      <title>Webcams de Asturias - El tiempo en Asturias en directo desde nuestras cámaras</title>
      <!--<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />-->
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
      <meta name="Author" content="Red de Webcams Asturias de Asturias">
      <meta name="Subject" content="Cámaras web en Asturias, España. El tiempo en Asturias en directo">
      <meta name="Description" content="Webcams de Asturias es la red de cámaras web propiedad de Himalia Tecnologías instalada por toda la región. Asturias en directo las 24 horas del día">
      <meta name="Keywords" content="España, Spain, Webcam. Cámara IP, Turismo. Meteorología, Asturias, Costa, Playas, Montaña, Tiempo, Oviedo, Gijón">
      <meta name="Language" content="Spanish">
      <meta name="Distribution" content="Global">
      <meta name="Robots" content="All">
      <meta name="publisuites-verify-code" content="aHR0cHM6Ly93ZWJjYW1zZGVhc3R1cmlhcy5jb20=" />
      <meta name="getlinko-verify-code" content="getlinko-verify-5af6381d8f5a388cc822b5c09d7010959ba60342"/>
      <link rel='stylesheet' href='/infoasturias/Estilos/hojaEstilos.css' type='text/css'/>
      <link type="text/css" rel="stylesheet" href="/css/general.css" media="all" />
      <link type="text/css" rel="stylesheet" href="/css/bootstrap.css" media="all">
      <script type="text/javascript" src="https://webcamsdeasturias.com/js/cookie.js"></script>
      <link rel="icon" href="https://www.webcamsdeasturias.com/favicon.ico" type="image/x-icon" />

<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer','GTM-NC8XL24S');</script>
<noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-NC8XL24S"
height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>

</head>

<body>

<div id="contenedor">

<div id="centrado">
	
<?php if(!isset($_SESSION["nick"])){ 
 $array = array("www.jairecanoas.com/descenso-del-sella.php","www.villademestas.com","www.aquassport.com","www.hoteleladia.es","www.kia.com/es/concesionarios/asturconsa/quiero-un-kia/promociones/feria-asturias/","www.kia.com/es/concesionarios/asturconsa/quiero-un-kia/promociones/feria-asturias/");
 $alts = array("Descenso del Sella","Alojamiento en Asturias","Descenso del Sella","Alojamiento en Cangas de Onís","Asturconsa - Promoción Feria Asturias","Asturconsa - Promoción Feria Asturias");
 $ids = array(8,13,9,100);
 $aux = rand(0,2);
?>

<?php 
if($aux<4){
?>
<a class="gestionPublicidad" data-url="<?php echo "https://".$array[$aux]; ?>" data-id="<?php echo $ids[$aux]; ?>" data-pos="1" href="https://<?php echo $array[$aux]; ?>">
<img width="978px" border="0" src="/banners/h_<?php echo $aux?>.jpg" title="<?php echo $alts[$aux] ?>" alt="<?php echo $alts[$aux] ?>" width="975px" style="padding:0px; margin:0px;"/>
</a>
<?php
}else{
?>
<a class="gestionPublicidad" data-url="<?php echo "https://".$array[$aux]; ?>" data-id="<?php echo $ids[$aux]; ?>" data-pos="1" href="https://<?php echo $array[$aux]; ?>">
<img width="978px" border="0" src="/banners/asturconsa.gif" title="<?php echo $alts[$aux] ?>" alt="<?php echo $alts[$aux] ?>" width="975px" style="padding:0px; margin:0px;"/>
</a>

<?php 
}}; ?> 
 

<?php
include	"./nuevacabecera.php"
?>

		<!-- contenido -->
		<div id="contenido1">
	
			<div class="salto"></div>

<?php if(!isset($_SESSION["nick"])){ ?>
<p align="center">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<ins class="adsbygoogle"
     style="display:inline-block;width:700px;height:100px"
     data-ad-client="ca-pub-9312774265223578"
     data-ad-slot="6992727350"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</p>
<?php }; ?> 

<div class="salto"></div>
<h1>La red de Webcams de Asturias, las ventanas al paraíso</h2>		
<div class="salto"></div>
			<!-- contenido destacados -->
			<div id="camDestacadas">
				<!-- esquina izq sup -->
				<div class="esquinaIS">
					<!-- esquina derecha sup -->
					<div class="esquinaDS">
						<div class="camDestacada">
							<div class="camara1">
								<div class="imagen">
<?php echo $novedad->getPortada(); ?></div>
								<div class="pieNovedad">
									<p><strong>Novedad</strong></p>
								</div>
								<div class="info">
									<div class="nombre">
										<div>
											<strong>Ubicaci&oacute;n</strong><br />
					<a href="<?php echo $gestion_camaras->getUrlFriendly($novedad->getId()); ?>">						<span><strong><?php echo $novedad->getNombrePueblo().": ".$novedad->getNombre(); ?></strong></span>
										</a></div>
									</div>
									<div class="descripcion">
										<div>
											<strong>Descripci&oacute;n</strong>
											<p><a href="<?php echo $gestion_camaras->getUrlFriendly($novedad->getId()); ?>" title="Visitar cámara"><?php echo substr($novedad->getDescripcion(),0,200); ?></a>... <a href="<?php echo $gestion_camaras->getUrlFriendly($novedad->getId()); ?>" title="Leer más">[+]</a></p>
										</div>
									</div>
								</div>
							</div>
						</div>
						
						<div class="camDestacada">
							<div class="camara2y3">
								<div class="imagen">

<?php echo $votada->getPortada(); ?></div>
								<div class="pie">
									<p><strong>La + votada</strong></p>
								</div>
								<div class="info">
									<div class="nombre">
										<div>
											<strong>Ubicaci&oacute;n</strong><br />
		<a href="<?php echo $gestion_camaras->getUrlFriendly($votada->getId()); ?>">									
<span><strong><?php echo $votada->getNombrePueblo().": ".$votada->getNombre(); ?></strong></span></a>
										</div>
									</div>
									<div class="descripcion">
										<div>
											<strong>Descripci&oacute;n</strong>
												<p><a href="<?php echo $gestion_camaras->getUrlFriendly($votada->getId()); ?>" title="Visitar cámara"><?php echo substr($votada->getDescripcion(),0,200); ?></a>... <a href="<?php echo $gestion_camaras->getUrlFriendly($votada->getId()); ?>" title="Leer más">[+]</a></p>
										</div>
									</div>
								</div>
							</div>
						</div>
						
						<div class="camDestacadaFin">
							<div class="camara2y3">
								<div class="imagen">

<?php echo $deldia->getPortada();?>
</div>
								<div class="pie">
									<p><strong>Cam del d&iacute;a</strong></p>
								</div>
								<div class="info">
									<div class="nombre">
										<div>
											<strong>Ubicaci&oacute;n</strong><br />
								
								<a href="<?php echo $gestion_camaras->getUrlFriendly($deldia->getId()); ?>">
											<span><strong><?php echo $deldia->getNombrePueblo().": ".$deldia->getNombre(); ?></strong></span>
								</a>
										</div>
									</div>
									<div class="descripcion">
										<div>
											<strong>Descripci&oacute;n</strong>
											<p><a href="<?php echo $gestion_camaras->getUrlFriendly($deldia->getId()); ?>" title="Vísitar cámara"><?php echo substr($deldia->getDescripcion(),0,200); ?></a>... <a href="<?php echo $gestion_camaras->getUrlFriendly($deldia->getId()); ?>" title="Leer más">[+]</a></p>
									</div>
									</div>
								</div>
							</div>
						</div>	
					</div>
				</div>
				<!-- ** borde inferior ** -->
				<div class="bordePie"><div><div></div></div></div>
			</div>	

<?php if(!isset($_SESSION["nick"])){ ?>
<p align="center">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<ins class="adsbygoogle"
     style="display:inline-block;width:700px;height:100px"
     data-ad-client="ca-pub-9312774265223578"
     data-ad-slot="6992727350"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</p>
<?php }; ?> 



<div id="avisoUso">
	<p>Estas cámaras NO graban, emiten en directo con fines meteorológicos, turísticos y promocionales.</p>
	<p>Queda prohíbida la utilización y reproducción de toda imagen sin autorización previa.</p>
	<p>Si desea disponer de uno de estos equipos en su localidad contacte en info@webcamsdeasturias.com.</p>
</div>	


 <div class="hero-unit">
<h2>Top 10 cams del día</h2>
	<?php                  

			$arrContextOptions=array(
      				"ssl"=>array(
            			"verify_peer"=>false,
            			"verify_peer_name"=>false,
        			),
    			);  

			$response = file_get_contents("./rankings/top-cams-day.inc", false, stream_context_create($arrContextOptions));

                        //echo utf8_encode($response); 
                        
                        echo $response;

			//require('./rankings/top-cams-day.inc'); 
			?>
</div>


<p align="center">
		
		<form id="frmSeleccionMapa" method="post" action="https://www.webcamsdeasturias.com/selectcam.php">
			<select style="width:375px;"  id="selectCam" name="id" style="float:left" >
				<option value="0" selected="selected">Seleccione una webcam </option>
										 <?php
										   $camaras=$gestion_camaras->getListaCamaras();
										   for($i=0;$i<count($camaras);$i++)
										   {?>
<option value="<?php echo $camaras[$i]->getId(); ?>"><?php echo $camaras[$i]->getNombrePueblo()." - ".$camaras[$i]->getNombre(); ?></option>
										   <?php 
     									   }
										   ?>
				</select>
				&nbsp;&nbsp;
				<input  type="image" id="seleccionaCam" name="seleccionaCam" src="http://webcamsdeasturias.com/imagenes/recursos/btnVerCam.gif" alt="Ver Cam" />
				&nbsp;		
				<b>Contamos con <?php $camaras=$gestion_camaras->getListaCamaras(); echo $gestion_camaras->getTotalCams();?> cámaras en Asturias</b>
		
		</form>
						
						

     </p>  
	 
 <div class="hero-unit">
	<h2>Tendencias | Lo + buscado en Webcams de Asturias</h2>
	<?php                  

			require('./top.inc'); 
			?>
			</div>





<?php if(!isset($_SESSION["nick"])){ ?>
<p align="center">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<ins class="adsbygoogle"
     style="display:inline-block;width:700px;height:100px"
     data-ad-client="ca-pub-9312774265223578"
     data-ad-slot="6992727350"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</p>
<?php }else{ ?>
<table border="0" width="100%">
<tr>
  <td align="center"><span style="color:grey; font-weight:bold; font-size:16px;">Instaladas</span></td>
  <td align="center"><span style="color:grey; font-weight:bold; font-size:16px;">En mantenimiento</span></td>
  <td align="center"><span style="color:grey; font-weight:bold; font-size:16px;">En instalación</span></td>
  <td align="center"><span style="color:grey; font-weight:bold; font-size:16px;">Cams HD</span></td>
  <td align="center"><span style="color:grey; font-weight:bold; font-size:16px;">Plan de mejora</span></td>
</tr>
<tr>

  <td align="center" style="padding-top:10px;"><span style="color:grey; font-weight:bold; font-size:20px;"><?php echo $gestion_camaras->getCamsInstaladas(); ?></span></td>
   <td align="center" style="padding-top:10px;"><span style="color:gray; font-weight:bold; font-size:20px;"><a href="
https://www.webcamsdeasturias.com/asturias/infocams/webcams/en-mantenimiento/3/"><?php echo $gestion_camaras->getCamsMantenimiento(); ?></a></span></td>  
<td align="center" style="padding-top:10px;"><span style="color:gray; font-weight:bold; font-size:20px;"><a href="https://www.webcamsdeasturias.com/asturias/infocams/webcams/en-instalacion/1/"><?php echo $gestion_camaras->getCamsEnInstalacion(); ?></a></span></td>
  <td align="center" style="padding-top:10px;"><span style="color:gray; font-weight:bold; font-size:20px;"><a href="https://www.webcamsdeasturias.com/asturias/infocams/webcams/hd/2/"><?php echo $gestion_camaras->getCamsHD(); ?></a></span></td>
  <td align="center" style="padding-top:10px;"><span style="color:gray; font-weight:bold; font-size:20px;"><a href="
https://www.webcamsdeasturias.com/asturias/infocams/webcams/pendiente-de-mejora/4/"><?php echo $gestion_camaras->getCamsMejora(); ?></a></span></td>
</tr>
</table> 
<?php } ?>
<br/>
  
			 <div class="hero-unit">
	<h2>Webcams de Asturias, concejo a concejo</h2>
			<?php
		        require('./listaConcejos.inc');

			$arrContextOptions=array(
      				"ssl"=>array(
            			"verify_peer"=>false,
            			"verify_peer_name"=>false,
        			),
    			);  
			$response = file_get_contents("./listaConcejos.inc", false, stream_context_create($arrContextOptions));
                        //echo utf8_encode($response); 
                      
                        //echo $response;


?></div>

<p>
Asturias es una tierra de contrastes y diversidad cultural que merece ser explorada en profundidad. Con su historia milenaria, su rica gastronomía, sus impresionantes paisajes y la hospitalidad de su gente, esta comunidad autónoma del norte de España se ha convertido en un destino turístico cada vez más popular.
</p><p>
Si desea descubrir todos los rincones de esta hermosa región, la red de webcams de Asturias es su mejor aliado. Desde las montañas de los Picos de Europa hasta las playas de la costa cantábrica, pasando por las principales ciudades y pueblos de la región, nuestras cámaras en vivo le ofrecen una visión privilegiada y en tiempo real de todo lo que ocurre en Asturias.
</p><p>
Con un total de más de 170 cámaras en toda la región, nuestras emisiones en directo permiten a los visitantes disfrutar de las maravillas de Asturias desde la comodidad de su hogar, planear sus vacaciones y explorar los lugares que más les interesen antes de su llegada.
</p><p>
No importa si desea conocer la espectacular costa asturiana, las montañas y bosques de la región o los encantadores pueblos que salpican el paisaje, nuestra red de webcams lo tiene cubierto. Además, nuestra tecnología avanzada garantiza la mejor calidad de imagen y sonido para que disfrute de una experiencia inolvidable.
</p><p>
Si está pensando en visitar Asturias o simplemente quiere conocer más sobre esta tierra mágica, no dude en explorar nuestro sitio web y contactarnos para obtener más información sobre nuestras cámaras en vivo. Estaremos encantados de ayudarlo a descubrir todos los tesoros de esta región única.
</p>
<br/>

<?php if(!isset($_SESSION["nick"])){ ?>	 
<p align="center">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<ins class="adsbygoogle"
     style="display:inline-block;width:700px;height:100px"
     data-ad-client="ca-pub-9312774265223578"
     data-ad-slot="6992727350"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</p>
<?php } ?>

	<h2>Oferta de alojamientos en Asturias, los mejores hoteles en Oviedo, Gijón, Avilés, Picos de Europa</h2>
<iframe src="https://www.stay22.com/embed/gm?aid=webcamsdeasturias&lat=43.3602900&lng=-5.8447600" id="stay22-widget" width="100%" height="460" frameborder="0"></iframe>

<br/>

<?php
			require('./noticias.inc'); 
		?>    

<?php if(!isset($_SESSION["nick"])){ ?>	 
<p align="center">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<ins class="adsbygoogle"
     style="display:inline-block;width:700px;height:100px"
     data-ad-client="ca-pub-9312774265223578"
     data-ad-slot="6992727350"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</p>
<?php } ?>




			
			<!-- ** ENLACES ** -->
			<div class="enlaces">
			  
			</div>
			
			<!-- PIE -->
			<div id="pie">
			   <?php require('./pie.inc'); ?>
			</div>
		</div>
		

		<!-- Columna derecha (registro,noticias,...)-->
		<div id="columnaD1">
			<!-- ** registro usuarios -->
		
			
<?php if(!isset($_SESSION["nick"])){ ?>			
<p align="center"><a href="https://www.webcamsdeasturias.com/alta-socios-webcams.html"><img src="https://www.webcamsdeasturias.com/imagenes/socio_lateral.png" alt="Únete a Webcams de Asturias" width="175" border="0"/></a></p>
<?php } ?>

<ul class="nav nav-tabs nav-stacked">
<li><a target="_blank" href="https://www.hispacams.com">Webcams España</a></li>
<li><a href="https://www.webcamsdeasturias.com/cms/informacion-general/te-gustaria-instalar-una-de-nuestras-camaras-en-tu-localidad/11/">Instalar webcam</a></li>
<li><a href="https://www.webcamsdeasturias.com/rankings-webcams-de-asturias.html">Tops 10 | Rankings</a></li>
<li><a href="https://www.webcamsdeasturias.com/contactar-con-webcams-de-asturias.html">Contacta con nosotros</a></li>
<li><a href="https://www.facebook.com/webcamsdeasturias"><b>Facebook</b></a></li>  
<li><a href="https://twitter.com/wcamsasturias"><b>Twitter</b></a></li>     
</ul>
      
</p>


<div class="miniCam">

				<div class="imagen">
					<div><a href="/montanas-y-sierras-de-asturias/3/" title="Sierras y cordilleras de Asturias"><img src="https://www.hispacams.com/get_imagen_ws.php?id=53" alt="Sierras y Cordilleras de Asturias"/></a></div>
				</div>
<a href="/montanas-y-sierras-de-asturias/3/" title="La monta&ntilde;a"><img src="imagenes/recursos/flechaGris.gif" alt="Flecha gris"/> <strong>La monta&ntilde;a</strong></a>
			</div>

<div class="miniCam"><br/>
				
				
				<div class="imagen">
					<div><a href="/los-rios-de-asturias/5/" title="Los ríos"><img src="https://www.hispacams.com/get_imagen_ws.php?id=55" alt="Ríos"/></a></div>
				</div>
<a href="/los-rios-de-asturias/5/" title="Los ríos"><img src="imagenes/recursos/flechaGris.gif" alt="Flecha gris"/> <strong>Los ríos</strong></a>
			</div>

<div class="miniCam"><br/>
				
				
				<div class="imagen">
					<div><a href="/los-pueblos-y-ciudades-de-asturias/4/" title="Poblaciones"><img src="https://www.hispacams.com/get_imagen_ws.php?id=10" alt="Poblaciones"/></a></div>
				</div>
<a href="/los-pueblos-y-ciudades-de-asturias/4/" title="Poblaciones"><img src="imagenes/recursos/flechaGris.gif" alt="Flecha gris"/> <strong>Poblaciones</strong></a>
			</div>

<div class="miniCam"><br/>
				
				<div class="imagen">
					<div><a href="/los-puertos-y-muelles-de-asturias/2/" title="Los puertos de la costa asturiana"><img src="https://www.hispacams.com/get_imagen_ws.php?id=27" alt="La costa, Webcams situadas en la costa asturiana"/></a></div>
				</div>
<a href="/los-puertos-y-muelles-de-asturias/2/" title="La costa"><img src="imagenes/recursos/flechaGris.gif" alt="Flecha gris"/> <strong>Los puertos</strong></a>
			</div>

<div class="miniCam"><br/>
				<div class="imagen">
					<div><a href="/las-playas-de-asturias/7/" title="Las playas de la costa asturiana"><img src="https://www.hispacams.com/get_imagen_ws.php?id=166" alt="Las playas en directo"/></a></div>
				</div>
<a href="/las-playas-de-asturias/7/" title="Las playas"><img src="imagenes/recursos/flechaGris.gif" alt="Flecha gris"/> <strong>Las playas</strong></a>
			</div>

<div class="salto"></div>

<?php if(!isset($_SESSION["nick"])){ ?>

<p align="center" style="margin-top:25px"><a href="https://www.elbuscolu.com"><img src="./imagenes/logoProviBuscolu.png" alt="Comunidad de noticias del oriente de Asturias" width="175" height="85" border="0"/></a></p>

<br/>

<?php } ?>


<?php if(!isset($_SESSION["nick"])){ ?>			
<p align="center"><a href="https://pl.polskiesloty.com/bonus-bez-depozytu/"><img alt="Polskie Sloty bonus bez depozytu" title="Polskie Sloty bonus bez depozytu" src="https://www.webcamsdeasturias.com/banners/minipolskie.png" alt="Mini Polskie" width="175" border="0"/></a></p>
<?php } ?>

<br/>


<div class="salto"></div>

		<!-- ** NOTICIAS ** -->
			<div class="noticias">

			
	                        <h3 class="tituloComentarios">COMENTARIOS</h3>
				<?php 
				$comentarios=$gestion_comentarios->getListaComentariosTodos(8);
			    
				for($i=0;$i<count($comentarios);$i++)
				 {
				?>
				
				<div>   
					<h2><a href='<?php echo $gestion_camaras->getUrlFriendly($comentarios[$i]->getCamara()); ?>' title="Ver comentario"><?php echo $gestion_camaras->getCamara($comentarios[$i]->getCamara())->getNombre(); ?></a></h2>
					<div class="desarrollo">
						<div class="fecha"><?php echo $comentarios[$i]->getFecha(); ?></div>
						<div class="ampliar"><p>
						 <?php 
						   echo substr($comentarios[$i]->getTexto(),0,100);
						 ?>

						  ...<a href="<?php echo $gestion_camaras->getUrlFriendly($comentarios[$i]->getCamara()); ?>">[+]</a>
						</p>
					   </div>
					 </div>
				</div>
				
				
				<?php 
				 }
				?>


			<!-- ** tags ** -->

<?php if(!isset($_SESSION["nick"])){ ?> 

				</div>
				<?php } ?>
			</div>

<?php if(!isset($_SESSION["nick"])){ ?>		


<?php } ?>


		</div>
		
	</div>

</div>

</body>
</html>


