// JavaScript específico para la página de detalle de cámara

// Función para generar slug a partir de un nombre
function generateSlug(nombre) {
    return nombre
        .toLowerCase()
        .normalize('NFD')
        .replace(/[\u0300-\u036f]/g, '') // Eliminar acentos
        .replace(/[^a-z0-9]+/g, '-') // Reemplazar caracteres especiales con guiones
        .replace(/^-+|-+$/g, ''); // Eliminar guiones al inicio y final
}

document.addEventListener('DOMContentLoaded', function() {
    // Obtener slug de la cámara desde la URL
    const path = window.location.pathname;
    const slug = path.split('/').pop().replace('.html', '') || path.split('/').pop();
    
    // Si no hay slug o es 'detalle.html', usar slug por defecto
    const camaraSlug = (slug && slug !== 'detalle.html' && slug !== 'detalle') 
        ? slug 
        : 'santa-elena-playa-ballenita';

    // Cargar información de la cámara
    loadCamaraInfo(camaraSlug);

    // Simular carga del video (en producción aquí iría la URL real del stream)
    simulateVideoLoad();
});

function loadCamaraInfo(camaraSlug) {
    // Datos de las cámaras (en producción esto vendría de una API)
    const camaras = {
        'santa-elena-playa-ballenita': {
            id: '1',
            nombre: 'Santa Elena - Playa Ballenita',
            slug: 'santa-elena-playa-ballenita',
            ubicacion: 'Santa Elena, Ecuador',
            lat: -2.1985575,
            lng: -80.8611329,
            descripcion: 'Hermosa playa con vista al océano Pacífico. Disfruta de las olas, la brisa marina y los atardeceres espectaculares.',
            categoria: 'Playa',
            estado: 'Activa',
            calidad: 'HD - Alta definición',
            streamUrl: 'https://rtsp.me/embed/9kbKi9AG/',
            colaborador: {
                nombre: 'Hostería Mirador Farallón Dillon',
                descripcion: 'Disfruta de una experiencia única con vistas espectaculares al océano Pacífico. Hospedaje de calidad en Santa Elena.',
                url: 'https://www.miradorfarallondillon.com',
                mostrar: true
            }
        }
    };

    const camara = camaras[camaraSlug];
    
    if (!camara) {
        // Redirigir a 404 o página principal si no se encuentra
        console.error('Cámara no encontrada:', camaraSlug);
        window.location.href = 'index.html';
        return;
    }
    
    // Actualizar título y meta tags para SEO
    updateSEOTags(camara);
    // Actualizar información si es necesario
    console.log('Cámara cargada:', camara);
    
    // Cargar datos meteorológicos
    if (camara.lat && camara.lng) {
        loadWeatherData(camara.lat, camara.lng);
    }
    
    // Mostrar/ocultar banner del colaborador
    const sponsorBanner = document.getElementById('sponsorBanner');
    if (sponsorBanner && camara.colaborador && camara.colaborador.mostrar) {
        // Actualizar información del colaborador
        const sponsorTitle = sponsorBanner.querySelector('.sponsor-title');
        const sponsorDescription = sponsorBanner.querySelector('.sponsor-description');
        const sponsorLink = sponsorBanner.querySelector('.btn-sponsor');
        
        if (sponsorTitle) sponsorTitle.textContent = camara.colaborador.nombre;
        if (sponsorDescription) sponsorDescription.textContent = camara.colaborador.descripcion;
        if (sponsorLink && camara.colaborador.url) {
            sponsorLink.href = camara.colaborador.url;
        }
        
        sponsorBanner.style.display = 'block';
    } else if (sponsorBanner) {
        sponsorBanner.style.display = 'none';
    }
}

// Función para actualizar meta tags SEO
function updateSEOTags(camara) {
    // Actualizar título
    document.title = `${camara.nombre} - Webcam en Vivo | ECURAICES WEBCAMS`;
    
    // Actualizar o crear meta description
    let metaDescription = document.querySelector('meta[name="description"]');
    if (!metaDescription) {
        metaDescription = document.createElement('meta');
        metaDescription.name = 'description';
        document.head.appendChild(metaDescription);
    }
    metaDescription.content = `Mira ${camara.nombre} en vivo. ${camara.descripcion} Transmisión 24/7 en alta definición.`;
    
    // Actualizar o crear meta keywords
    let metaKeywords = document.querySelector('meta[name="keywords"]');
    if (!metaKeywords) {
        metaKeywords = document.createElement('meta');
        metaKeywords.name = 'keywords';
        document.head.appendChild(metaKeywords);
    }
    metaKeywords.content = `${camara.nombre}, webcam en vivo, ${camara.ubicacion}, ${camara.categoria}, Ecuador, streaming en vivo`;
    
    // Actualizar Open Graph tags
    updateOpenGraphTags(camara);
    
    // Actualizar canonical URL
    updateCanonicalURL(camara);
}

// Función para actualizar Open Graph tags
function updateOpenGraphTags(camara) {
    const ogTags = {
        'og:title': `${camara.nombre} - Webcam en Vivo | ECURAICES WEBCAMS`,
        'og:description': camara.descripcion,
        'og:type': 'website',
        'og:url': window.location.href,
        'og:image': window.location.origin + '/recursos/image.png'
    };
    
    Object.keys(ogTags).forEach(property => {
        let tag = document.querySelector(`meta[property="${property}"]`);
        if (!tag) {
            tag = document.createElement('meta');
            tag.setAttribute('property', property);
            document.head.appendChild(tag);
        }
        tag.content = ogTags[property];
    });
}

// Función para actualizar canonical URL
function updateCanonicalURL(camara) {
    let canonical = document.querySelector('link[rel="canonical"]');
    if (!canonical) {
        canonical = document.createElement('link');
        canonical.rel = 'canonical';
        document.head.appendChild(canonical);
    }
    canonical.href = `https://www.ecuraices.com/webcams/${camara.slug}.html`;
}

function simulateVideoLoad() {
    // El iframe se carga automáticamente, no necesitamos simular carga
    const videoIframe = document.getElementById('videoIframe');
    if (videoIframe) {
        // El iframe ya está configurado para cargar automáticamente
        console.log('Video stream cargado');
    }
}

function toggleFullscreen() {
    const videoIframe = document.getElementById('videoIframe');
    if (!videoIframe) return;

    if (!document.fullscreenElement) {
        // Intentar pantalla completa del iframe
        if (videoIframe.requestFullscreen) {
            videoIframe.requestFullscreen();
        } else if (videoIframe.webkitRequestFullscreen) {
            videoIframe.webkitRequestFullscreen();
        } else if (videoIframe.msRequestFullscreen) {
            videoIframe.msRequestFullscreen();
        } else {
            // Fallback: pantalla completa del contenedor
            const videoContainer = document.querySelector('.video-wrapper');
            if (videoContainer) {
                if (videoContainer.requestFullscreen) {
                    videoContainer.requestFullscreen();
                } else if (videoContainer.webkitRequestFullscreen) {
                    videoContainer.webkitRequestFullscreen();
                } else if (videoContainer.msRequestFullscreen) {
                    videoContainer.msRequestFullscreen();
                }
            }
        }
    } else {
        if (document.exitFullscreen) {
            document.exitFullscreen();
        } else if (document.webkitExitFullscreen) {
            document.webkitExitFullscreen();
        } else if (document.msExitFullscreen) {
            document.msExitFullscreen();
        }
    }
}

function refreshVideo() {
    const videoIframe = document.getElementById('videoIframe');
    
    if (videoIframe) {
        // Recargar el iframe para refrescar el stream
        const currentSrc = videoIframe.src;
        videoIframe.src = '';
        setTimeout(() => {
            videoIframe.src = currentSrc;
        }, 100);
    }
}

function shareCamera(url, title) {
    if (navigator.share) {
        navigator.share({
            title: title,
            text: 'Mira esta cámara en vivo en ECURAICES WEBCAMS',
            url: url
        }).catch(err => {
            console.log('Error al compartir:', err);
            fallbackShare(url);
        });
    } else {
        fallbackShare(url);
    }
}

function fallbackShare(url) {
    // Crear un input temporal para copiar al portapapeles
    const input = document.createElement('input');
    input.value = url;
    document.body.appendChild(input);
    input.select();
    document.execCommand('copy');
    document.body.removeChild(input);
    
    // Mostrar notificación
    showNotification('Enlace copiado al portapapeles');
}

function showNotification(message) {
    // Crear elemento de notificación
    const notification = document.createElement('div');
    notification.className = 'notification';
    notification.textContent = message;
    notification.style.cssText = `
        position: fixed;
        bottom: 20px;
        right: 20px;
        background: #2574b4;
        color: white;
        padding: 1rem 2rem;
        border-radius: 10px;
        box-shadow: 0 4px 15px rgba(0,0,0,0.2);
        z-index: 9999;
        animation: slideIn 0.3s ease;
    `;
    
    document.body.appendChild(notification);
    
    setTimeout(() => {
        notification.style.animation = 'slideOut 0.3s ease';
        setTimeout(() => {
            document.body.removeChild(notification);
        }, 300);
    }, 3000);
}

// Agregar estilos de animación si no existen
if (!document.getElementById('notification-styles')) {
    const style = document.createElement('style');
    style.id = 'notification-styles';
    style.textContent = `
        @keyframes slideIn {
            from {
                transform: translateX(100%);
                opacity: 0;
            }
            to {
                transform: translateX(0);
                opacity: 1;
            }
        }
        @keyframes slideOut {
            from {
                transform: translateX(0);
                opacity: 1;
            }
            to {
                transform: translateX(100%);
                opacity: 0;
            }
        }
    `;
    document.head.appendChild(style);
}

// Función para cargar datos meteorológicos reales
function loadWeatherData(lat, lng) {
    // Usar Open-Meteo API (gratuita, sin API key requerida)
    const apiUrl = `https://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lng}&current=temperature_2m,wind_speed_10m,visibility&timezone=America/Guayaquil`;
    
    fetch(apiUrl)
        .then(response => {
            if (!response.ok) {
                throw new Error('Error al obtener datos meteorológicos');
            }
            return response.json();
        })
        .then(data => {
            if (data.current) {
                // Actualizar temperatura
                const tempElement = document.getElementById('weather-temp');
                if (tempElement && data.current.temperature_2m !== undefined) {
                    tempElement.textContent = `${Math.round(data.current.temperature_2m)}°C`;
                }
                
                // Actualizar viento
                const windElement = document.getElementById('weather-wind');
                if (windElement && data.current.wind_speed_10m !== undefined) {
                    // Convertir de m/s a km/h
                    const windKmh = Math.round(data.current.wind_speed_10m * 3.6);
                    windElement.textContent = `${windKmh} km/h`;
                }
                
                // Actualizar visibilidad
                const visibilityElement = document.getElementById('weather-visibility');
                if (visibilityElement && data.current.visibility !== undefined) {
                    // Convertir metros a descripción
                    const visibilityKm = data.current.visibility / 1000;
                    let visibilityText;
                    if (visibilityKm >= 10) {
                        visibilityText = 'Excelente';
                    } else if (visibilityKm >= 5) {
                        visibilityText = 'Buena';
                    } else if (visibilityKm >= 2) {
                        visibilityText = 'Moderada';
                    } else {
                        visibilityText = 'Reducida';
                    }
                    visibilityElement.textContent = visibilityText;
                }
            }
        })
        .catch(error => {
            console.error('Error al cargar datos meteorológicos:', error);
            // Mostrar valores por defecto en caso de error
            const tempElement = document.getElementById('weather-temp');
            const windElement = document.getElementById('weather-wind');
            const visibilityElement = document.getElementById('weather-visibility');
            
            if (tempElement) tempElement.textContent = 'N/A';
            if (windElement) windElement.textContent = 'N/A';
            if (visibilityElement) visibilityElement.textContent = 'N/A';
        });
}


