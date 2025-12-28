// Mapa de geolocalización para la página de detalle de cámara

document.addEventListener('DOMContentLoaded', function() {
    // Obtener slug de la cámara desde la URL
    const path = window.location.pathname;
    const slug = path.split('/').pop().replace('.html', '') || path.split('/').pop();
    const camaraSlug = (slug && slug !== 'detalle.html' && slug !== 'detalle') 
        ? slug 
        : 'santa-elena-playa-ballenita';
    
    // Datos de las cámaras (en producción esto vendría de una API)
    const camaras = {
        'santa-elena-playa-ballenita': {
            nombre: 'Santa Elena - Playa Ballenita',
            lat: -2.1985575,
            lng: -80.8611329,
            categoria: 'Playa',
            descripcion: 'Hermosa playa con vista al océano Pacífico'
        }
    };
    
    const camara = camaras[camaraSlug];
    
    if (!camara) {
        console.error('Cámara no encontrada');
        return;
    }
    
    // Inicializar mapa centrado en la ubicación de la cámara
    const map = L.map('mapaDetalle').setView([camara.lat, camara.lng], 14);
    
    // Agregar capa de OpenStreetMap
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '© OpenStreetMap contributors',
        maxZoom: 18
    }).addTo(map);
    
    // Icono personalizado para la cámara
    const cameraIcon = L.divIcon({
        className: 'custom-marker-detalle',
        html: '<div class="marker-camera-detalle"><i class="bi bi-camera-video-fill"></i></div>',
        iconSize: [50, 50],
        iconAnchor: [25, 50],
        popupAnchor: [0, -50]
    });
    
    // Agregar marcador
    const marker = L.marker([camara.lat, camara.lng], { icon: cameraIcon })
        .addTo(map)
        .bindPopup(`
            <div class="popup-camara-detalle">
                <h6 class="mb-2"><strong>${camara.nombre}</strong></h6>
                <p class="mb-2 small text-muted">${camara.descripcion}</p>
                <span class="badge bg-primary">${camara.categoria}</span>
            </div>
        `)
        .openPopup();
    
    // Agregar círculo para mostrar área aproximada
    L.circle([camara.lat, camara.lng], {
        color: '#2574b4',
        fillColor: '#3288cc',
        fillOpacity: 0.2,
        radius: 500 // 500 metros
    }).addTo(map);
});


