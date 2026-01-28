# eIWconfig

```{index} single: eIWconfig
```

<img width="1398" height="243" alt="image" src="https://github.com/user-attachments/assets/9688743e-0091-4849-bd83-351768377028" />

* * * * * * * * * *

## Einleitung
Der eIWconfig Funktionsblock dient als Service Interface für die Konfiguration von eIO-Instanzen. Er ermöglicht die Einstellung von Schwellwerten und Gradienten für industrielle IO-Operationen.

![eIWconfig](eIWconfig.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **CONF**: Konfigurationsanforderung - löst die Konfiguration der eIO-Instanz aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung des angeforderten Services - signalisiert den Abschluss der Konfiguration

### **Daten-Eingänge**
- **ST** (WORD): "Smaller than" - Unterer Schwellwert
- **BT** (WORD): "Bigger than" - Oberer Schwellwert
- **GRAD** (WORD): Gradient in Prozent - Steilheit der Übergänge

### **Daten-Ausgänge**
- **STATUS** (WSTRING): Service Status - Rückmeldung über den Konfigurationsvorgang

### **Adapter**
- **eIW**: Verbindung zur eIO-Instanz (Typ: eclipse4diac::io::eio::eGenAdapter)

## Funktionsweise
Der Funktionsblock empfängt über das CONF-Ereignis eine Konfigurationsanforderung zusammen mit den Parametern ST, BT und GRAD. Diese Parameter werden über den eIW-Adapter an die eIO-Instanz übertragen. Nach erfolgreicher Konfiguration bestätigt der Block den Vorgang durch das CNF-Ereignis und liefert über STATUS eine Statusrückmeldung.

## Technische Besonderheiten
- Verwendet WORD-Datentypen für alle numerischen Eingänge
- STATUS-Ausgang als WSTRING für detaillierte Statusinformationen
- Adapter-basierte Architektur für lose Kopplung zur eIO-Instanz

## Zustandsübersicht
1. **Bereit**: Wartet auf CONF-Ereignis
2. **Konfigurierend**: Verarbeitet Konfigurationsparameter
3. **Bestätigend**: Sendet CNF-Ereignis mit Statusinformation

## Anwendungsszenarien
- Konfiguration von IO-Schwellwerten in Automatisierungssystemen
- Einstellung von Filterparametern für Sensorsignale
- Dynamische Anpassung von Grenzwerten in Regelungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen IO-Konfigurationsblöcken bietet eIWconfig eine erweiterte Funktionalität mit Gradientensteuerung und Adapter-basierter Architektur für höhere Flexibilität.

## Fazit
Der eIWconfig Funktionsblock stellt eine flexible und erweiterbare Lösung für die Konfiguration von eIO-Instanzen dar, die durch ihre Adapter-basierte Architektur und umfangreiche Parametrierungsmöglichkeiten besticht.