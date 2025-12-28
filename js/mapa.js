// Mapa de geolocalización para la página principal

document.addEventListener('DOMContentLoaded', function() {
    // Coordenadas de Ecuador (centro del país)
    const ecuadorCenter = [-1.8312, -78.1834];
    
    // Inicializar mapa
    const map = L.map('map').setView(ecuadorCenter, 6);
    
    // Agregar capa de OpenStreetMap
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '© OpenStreetMap contributors',
        maxZoom: 18
    }).addTo(map);
    
    // Datos de las cámaras
    const camaras = [
        {
            id: 1,
            nombre: 'Santa Elena - Playa Ballenita',
            lat: -2.1985575,
            lng: -80.8611329,
            categoria: 'Playa',
            descripcion: 'Hermosa playa con vista al océano Pacífico',
            url: 'santa-elena-playa-ballenita.html',
            slug: 'santa-elena-playa-ballenita'
        }
        // Agregar más cámaras aquí cuando estén disponibles
    ];
    
    // Icono personalizado para las cámaras
    const cameraIcon = L.divIcon({
        className: 'custom-marker',
        html: '<div class="marker-camera"><i class="bi bi-camera-video-fill"></i></div>',
        iconSize: [40, 40],
        iconAnchor: [20, 40],
        popupAnchor: [0, -40]
    });
    
    // Agregar marcadores para cada cámara
    camaras.forEach(camara => {
        const marker = L.marker([camara.lat, camara.lng], { icon: cameraIcon })
            .addTo(map)
            .bindPopup(`
                <div class="popup-camara">
                    <h6 class="mb-2"><strong>${camara.nombre}</strong></h6>
                    <p class="mb-2 small text-muted">${camara.descripcion}</p>
                    <span class="badge bg-primary mb-2">${camara.categoria}</span>
                    <div class="mt-2">
                        <a href="${camara.url}" class="btn btn-sm btn-primary">
                            <i class="bi bi-play-circle"></i> Ver Cámara
                        </a>
                    </div>
                </div>
            `);
        
        // Agregar evento click para abrir el detalle
        marker.on('click', function() {
            window.location.href = camara.url;
        });
    });
    
    // Si hay solo una cámara, centrar el mapa en ella
    if (camaras.length === 1) {
        map.setView([camaras[0].lat, camaras[0].lng], 12);
    } else if (camaras.length > 1) {
        // Ajustar el zoom para mostrar todas las cámaras
        const group = new L.featureGroup(camaras.map(c => 
            L.marker([c.lat, c.lng])
        ));
        map.fitBounds(group.getBounds().pad(0.1));
    }
});


