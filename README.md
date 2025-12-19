# ECURAICES WEBCAMS

Portal web para la red de webcams de Ecuador. Una plataforma sencilla y moderna para visualizar cámaras en tiempo real desde diferentes ubicaciones del país.

## 🎨 Colores Corporativos

- **ECU (Amarillo dorado)**: `#eaab2b`
- **RAI (Azul)**: `#2574b4`
- **CES (Rojo)**: `#e2252d`
- **WEBCAMS (Azul claro)**: `#3288cc`
- **Gris claro**: `#ebeeea`
- **Negro/Marrón oscuro**: `#27211a`
- **Marrón**: `#a76755`
- **Gris**: `#636363`

## 📁 Estructura del Proyecto

```
Ecuraices/
├── index.html          # Página principal (Home)
├── categorias.html     # Sección de categorías
├── detalle.html        # Detalle de cámara individual
├── css/
│   └── styles.css      # Estilos personalizados
├── js/
│   ├── main.js        # JavaScript principal
│   └── detalle.js     # JavaScript para página de detalle
└── recursos/          # Recursos (imágenes, etc.)
```

## 🚀 Características

### Páginas

1. **Home (index.html)**
   - Hero section con logo y presentación
   - Preview de categorías
   - Cámaras destacadas
   - Footer con información de contacto

2. **Categorías (categorias.html)**
   - Grid de categorías disponibles
   - Lista de cámaras por categoría
   - Filtrado por categoría (vía parámetros URL)

3. **Detalle (detalle.html)**
   - Reproductor de video en vivo
   - Información detallada de la cámara
   - Controles de video (pantalla completa, actualizar, compartir)
   - Información del tiempo
   - Cámaras relacionadas

### Funcionalidades

- ✅ Diseño responsive con Bootstrap 5
- ✅ Navegación suave entre secciones
- ✅ Animaciones al hacer scroll
- ✅ Sistema de categorías
- ✅ Integración lista para streams de video
- ✅ Compartir cámaras
- ✅ Modo pantalla completa
- ✅ Breadcrumbs para navegación

## 📷 Cámaras Actuales

- **Santa Elena - Playa Ballenita**
  - Ubicación: Santa Elena, Ecuador
  - Categoría: Playas
  - Estado: Activa

## 🛠️ Tecnologías Utilizadas

- **HTML5**
- **CSS3** (con variables CSS para colores corporativos)
- **Bootstrap 5.3.0**
- **JavaScript (Vanilla)**
- **Bootstrap Icons**

## 📝 Notas de Desarrollo

### Integración de Video Streams

Para integrar un stream de video real, reemplazar en `detalle.html`:

```html
<!-- Actual -->
<div class="video-placeholder" id="videoStream">
    <!-- Placeholder -->
</div>

<!-- Con stream real (ejemplo) -->
<iframe 
    src="URL_DEL_STREAM" 
    frameborder="0" 
    allowfullscreen
    class="video-stream">
</iframe>
```

### Agregar Nuevas Cámaras

1. Agregar la cámara en `categorias.html` dentro de la categoría correspondiente
2. Crear una entrada en el objeto `camaras` en `js/detalle.js`
3. Agregar una tarjeta en la sección de cámaras destacadas en `index.html`

### Personalización de Colores

Los colores corporativos están definidos como variables CSS en `css/styles.css`:

```css
:root {
    --color-ecu: #eaab2b;
    --color-rai: #2574b4;
    --color-ces: #e2252d;
    /* ... */
}
```

## 🌐 Navegación

- **Home**: `/index.html`
- **Categorías**: `/categorias.html`
- **Categoría específica**: `/categorias.html?cat=playas`
- **Detalle de cámara**: `/detalle.html?id=1`

## 📱 Responsive

El sitio está completamente optimizado para:
- 📱 Móviles
- 📱 Tablets
- 💻 Desktop

## 🔮 Próximas Mejoras

- [ ] Integración con API de streams de video
- [ ] Sistema de búsqueda de cámaras
- [ ] Favoritos de cámaras
- [ ] Historial de visualización
- [ ] Notificaciones de nuevas cámaras
- [ ] Mapa interactivo con ubicaciones

## 📄 Licencia

© 2025 ECURAICES WEBCAMS. Todos los derechos reservados.


