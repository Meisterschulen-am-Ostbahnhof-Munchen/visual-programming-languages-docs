# logiBUS_LED_PWM_QX

```{index} single: logiBUS_LED_PWM_QX
```

<img width="1905" height="366" alt="image" src="https://github.com/user-attachments/assets/ff509262-3aeb-48fd-88e2-74c2323ab225" />

* * * * * * * * * *

## 🎧 Podcast

* [Digitale Gedächtnisse: Das SR-Flip-Flop im logiBUS®-System erklärt](https://podcasters.spotify.com/pod/show/logibus/episodes/Digitale-Gedchtnisse-Das-SR-Flip-Flop-im-logiBUS-System-erklrt-e36vksj)
* [ESP32 als Industrie-SPS: Revolution mit Eclipse 4diac und logiBUS®](https://podcasters.spotify.com/pod/show/logibus/episodes/ESP32-als-Industrie-SPS-Revolution-mit-Eclipse-4diac-und-logiBUS-e375dp6)
* [From Cable Chaos to Custom Control: How Logibus is Revolutionizing Agricultural Tech with Accessible ISOBUS](https://podcasters.spotify.com/pod/show/logibus/episodes/From-Cable-Chaos-to-Custom-Control-How-Logibus-is-Revolutionizing-Agricultural-Tech-with-Accessible-ISOBUS-e3767lq)
* [Logibus Revolution: Unpacking the "No Mapping" Future and Streamlined Development](https://podcasters.spotify.com/pod/show/logibus/episodes/Logibus-Revolution-Unpacking-the-No-Mapping-Future-and-Streamlined-Development-e375aph)
* [Logibus Unleashed: How Eliminating "Mapping" Simplifies Complex Systems and Boosts Usability](https://podcasters.spotify.com/pod/show/logibus/episodes/Logibus-Unleashed-How-Eliminating-Mapping-Simplifies-Complex-Systems-and-Boosts-Usability-e375a3m)

## 📺 Video

* [06. Mai 2025 Tag 6 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=g-LuUu-QFcI)
* [15. Apr. 2025  Tag 1 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=tlZC5rN_CUI)
* [17. Apr. 2025 Tag 2 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=hy2S94jOVi0)
* [2025 11 15 12 35 11 Montage Hutschienenmoped logiBUS® -- Teil 3 -- Gehäuse](https://www.youtube.com/watch?v=MPm4vLmD5RE)
* [2025 11 15 12 52 26 Montage Hutschienenmoped logiBUS® -- Teil 4 -- Aufbauten](https://www.youtube.com/watch?v=WeowCxZW70Y)

## Einleitung
Der logiBUS_LED_PWM_QX ist ein Ausgabeservice-Interface-Funktionsblock für boolesche Ausgabedaten mit PWM-Funktionalität für LED-Ansteuerung. Der Baustein ermöglicht die Ansteuerung von LED-Ausgängen mit konfigurierbaren Frequenzen und bietet eine standardisierte Schnittstelle für die Kommunikation mit logiBUS-I/O-Ressourcen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit Parametern QI, PARAMS, Output und FREQ
- **REQ**: Service-Anforderung mit Parametern QI und OUT

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit Parametern QO und STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation mit Parametern QO und STATUS

### **Daten-Eingänge**
- **QI**: BOOL - Ereignis-Eingangsqualifizierer
- **PARAMS**: STRING - Service-Parameter
- **OUT**: BOOL - Ausgabedaten zur Ressource
- **Output**: logiBUS_DO_S - Identifiziert den Ausgang (Output_Q1..Q8), Initialwert: Invalid
- **FREQ**: UINT - Definiert die LED-Frequenz und Priorität, Initialwert: LED_FREQ::LED_OFF

### **Daten-Ausgänge**
- **QO**: BOOL - Ereignis-Ausgangsqualifizierer
- **STATUS**: STRING - Service-Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock verwaltet die PWM-Ansteuerung von LED-Ausgängen über das logiBUS-System. Bei der Initialisierung (INIT-Event) werden die Ausgangskonfiguration, Frequenzeinstellungen und Service-Parameter übergeben. Über das REQ-Event können Ausgabedaten (OUT) gesendet werden, die dann mit der konfigurierten PWM-Frequenz auf den spezifizierten Ausgang (Output) angewendet werden.

## Technische Besonderheiten
- Unterstützt verschiedene LED-Frequenzen über den FREQ-Parameter
- Integrierte Fehlerbehandlung durch STATUS-Ausgabe
- Typisierte Ausgangsidentifikation über logiBUS_DO_S-Datentyp
- Initialisierung mit Invalid-Zustand für nicht konfigurierte Ausgänge
- Frequenzprioritätssteuerung für LED-Ansteuerung

## Zustandsübersicht
Der Baustein verfügt über folgende Betriebszustände:
- **Nicht initialisiert**: Vor INIT-Event, Ausgänge inaktiv
- **Initialisiert**: Nach erfolgreicher INIT-Verarbeitung, bereit für REQ-Operationen
- **Aktiv**: Während der PWM-Signalgenerierung
- **Fehler**: Bei ungültigen Parametern oder Konfigurationsfehlern

## Anwendungsszenarien
- Ansteuerung von Status-LEDs in industriellen Steuerungssystemen
- PWM-gesteuerte Beleuchtungssysteme
- Visuelle Signalgebung mit variabler Helligkeitssteuerung
- Prioritätsgesteuerte LED-Anzeigen in logiBUS-basierten Anwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgangsbausteinen bietet logiBUS_LED_PWM_QX erweiterte PWM-Funktionalität mit Frequenzsteuerung und prioritätsbasierter Ansteuerung. Die Integration in das logiBUS-Ökosystem ermöglicht eine standardisierte Kommunikation mit I/O-Ressourcen.

## Fazit
Der logiBUS_LED_PWM_QX ist ein spezialisierter Funktionsblock für anspruchsvolle LED-Ansteuerungsanwendungen in industriellen Automatisierungssystemen. Durch die PWM-Funktionalität, konfigurierbare Frequenzen und die Integration in das logiBUS-System bietet er eine leistungsstarke Lösung für visuelle Ausgabeszenarien mit hohen Anforderungen an Flexibilität und Zuverlässigkeit.