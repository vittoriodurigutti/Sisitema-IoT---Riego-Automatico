![Imagen de Portada](https://via.placeholder.com/800x400.png?text=Sistema+de+Riego+Automatizado) <!-- Reemplaza este enlace con una imagen relevante -->

# Sistema de Riego Automatizado mediante Clasificación con Orientación Residencial

### Proyecto de: Durigutti Vittorio

## Descripción
Este proyecto consiste en un **sistema de sensorización de humedad, pH y nutrientes**, complementado con un sistema actuador de riego reactivo a las condiciones específicas de las plantas. Tiene como objetivos principales:

- **Sensorización inalámbrica**: Uso de sensores inteligentes integrados.
- **Riego eficiente**: Implementación de un sistema de riego por goteo, configurable por canilla de riego y sensor.
- **Registro y control remoto**: Almacenamiento y monitoreo en tiempo real con interacción remota a través de un controlador.
- **Escalabilidad**: Sistema modular con nodos interconectados mediante tecnologías WiFi, BLE, LoRa y ESP-Now.
- **Gestión avanzada**: Integración de APIs para control y gestión de datos.
- **Bases de datos híbridas**:
  - Base de datos relacional para registro numérico.
  - Base de datos no relacional basada en documentos usando MongoDB.
- **Interfaz interactiva**: Desarrollo de una plataforma web y móvil para la interacción usuario-sistema.

---

![Sistema de Riego Automatizado](/E%20Assets/EsquemaFuncionamiento.PNG)

---

## Stack Tecnológico
### IDE y Gestión
- Visual Studio Code
- IDE Espressif
- Kanban para gestión ágil

### Bases de Datos
- MongoDB
- InfluxDB
- Postman (para pruebas y testeo)
- Lucidchart (para diseño de bases de datos y flujos)

### EDGE Computing
- PlatformIO
- Proteus
- FreeRTOS

### FOG Computing
- A definir según los requerimientos de escalabilidad y procesamiento.

### Cloud Computing
- A definir según necesidades de almacenamiento y análisis masivo.

---

## Estructura del Repositorio
La estructura del repositorio está organizada en carpetas y archivos específicos:

### A. Parámetros del Proyecto
- `/Diagramas`: Diagramas de red, funcionamiento, diseño e integración.
- `Descripcion_Teorica.md`: Descripción teórica extendida del proyecto.

### B. Investigación
- `/Datasheets`: Hojas de especificaciones de hardware.
- `/Bibliografia`: Fuentes y referencias relevantes.
- `/Informes_de_Funcionamiento`: Reportes sobre las pruebas del sistema.

### C. Prototipo
- `/Test_Unitarios`
  - `/Sensores`: Pruebas individuales de sensores.
  - `/Comunicacion`: Pruebas de conectividad entre nodos.
- `/Prototipos_Integracion`: Resultados de la integración de módulos.
- `/Prototipo_Middleware`: Arquitectura y prototipos middleware.
- `/Prototipo_BaseDeDatos`: Configuración inicial y diseño de bases de datos.
- `/Prototipo_WebApp_MovilApp`: Interfaces preliminares web y móvil.

### D. Presentación
- `/AudioVisuales`: Material multimedia para demostraciones.
- `Manual_de_Usuario.md`: Instrucciones detalladas de uso del sistema.
- `/Presentaciones_Teoricas`: Documentos para exposiciones.

### E. Assets
- `/Uso_General`: Recursos compartidos entre módulos.
- `Otros`: Archivos adicionales o accesorios.

---

## Licencia
Este proyecto está bajo la licencia **MIT**. Para más detalles, consulta el archivo `LICENSE.md`.
