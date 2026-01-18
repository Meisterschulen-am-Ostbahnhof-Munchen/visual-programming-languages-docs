# Port

```{index} single: Port
```
## 🎧 Podcast

* [Das Technologie-Panorama von 1863: Lanz & Comp. und die Revolution der deutschen Landwirtschaft durch Import, Innovation und Guano](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Das-Technologie-Panorama-von-1863-Lanz--Comp--und-die-Revolution-der-deutschen-Landwirtschaft-durch-Import--Innovation-und-Guano-e39auqa)
* [ESP32-S3-DevKitC-1 Doku-Analyse: Das Speicher-Monster (32MB Flash/16MB PSRAM) und die Macht der Dual-USB-Ports](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/ESP32-S3-DevKitC-1-Doku-Analyse-Das-Speicher-Monster-32MB-Flash16MB-PSRAM-und-die-Macht-der-Dual-USB-Ports-e39hamt)

## Einleitung
Der Port-Funktionsblock dient als Service Interface Function Block für die Konfiguration und Verwaltung von digitalen Ein-/Ausgängen auf einem EliteBoard-System. Er ermöglicht die Zuordnung von Pin-Namen zu physischen Ports über einen Adapter-Mechanismus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
- **Pin0** (STRING): Name des Pins 0
- **Pin1** (STRING): Name des Pins 1
- **Pin2** (STRING): Name des Pins 2
- **Pin3** (STRING): Name des Pins 3
- **Pin4** (STRING): Name des Pins 4
- **Pin5** (STRING): Name des Pins 5
- **Pin6** (STRING): Name des Pins 6
- **Pin7** (STRING): Name des Pins 7
- **Pin8** (STRING): Name des Pins 8
- **Pin9** (STRING): Name des Pins 9
- **Pin10** (STRING): Name des Pins 10
- **Pin11** (STRING): Name des Pins 11
- **Pin12** (STRING): Name des Pins 12
- **Pin13** (STRING): Name des Pins 13
- **Pin14** (STRING): Name des Pins 14
- **Pin15** (STRING): Name des Pins 15

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
- **PortInAdapter** (eclipse4diac::io::eliteboard::PortAdapter): Socket-Adapter für die Kommunikation mit dem Port-Subsystem

## Funktionsweise
Der Port-FB dient als Konfigurationsschnittstelle für bis zu 16 digitale Pins. Über die STRING-Eingänge können individuelle Pin-Namen vergeben werden, die über den PortAdapter an das darunterliegende System weitergegeben werden. Der Funktionsblock selbst führt keine direkten Ein-/Ausgabeoperationen durch, sondern stellt lediglich die Konfigurationsparameter bereit.

## Technische Besonderheiten
- Unterstützt Konfiguration von 16 digitalen Pins
- Verwendet STRING-Datentyp für Pin-Namen
- Implementiert als Service Interface Function Block
- Nutzt Adapter-Pattern für Hardware-Abstraktion
- Teil des eclipse4diac::io::eliteboard-Pakets

## Zustandsübersicht
Da es sich um einen reinen Konfigurationsbaustein ohne Ereignissteuerung handelt, besitzt der Port-FB keine expliziten Zustände. Die Konfiguration wird statisch über die Daten-Eingänge festgelegt.

## Anwendungsszenarien
- Konfiguration von digitalen Ein-/Ausgängen auf EliteBoard-Systemen
- Abstraktion von Hardware-Pins durch logische Namen
- Integration in größere Steuerungssysteme mit einheitlicher Pin-Verwaltung
- Wiederverwendbare Pin-Konfigurationen in verschiedenen Applikationen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu direkten GPIO-Bausteinen bietet der Port-FB eine höhere Abstraktionsebene durch die Verwendung von logischen Pin-Namen statt direkter Hardware-Adressierung. Er dient primär der Konfiguration, während andere Bausteine typischerweise die eigentliche Ein-/Ausgabe-Funktionalität bereitstellen.

## Fazit
Der Port-Funktionsblock stellt eine elegante Lösung für die konfigurationsbasierte Pin-Verwaltung in Eclipse 4diac-Systemen dar. Durch die Verwendung von Adaptern ermöglicht er eine klare Trennung zwischen Konfiguration und Hardware-Zugriff, was die Wartbarkeit und Portierbarkeit von Steuerungsapplikationen verbessert.