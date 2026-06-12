# ATM_AX_PULSE


![ATM_AX_PULSE](./ATM_AX_PULSE.svg)

*Bild nicht verfügbar*

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ATM_AX_PULSE** ist ein standardisierter Timerbaustein zur Erzeugung eines nicht nachtriggerbaren Impulses (non‑retriggerable). Er wird über die Adapter-Schnittstellen **PT** (ATM) und **Q** (AX) konfiguriert und ausgelesen. Der Baustein entspricht der IEC 61499‑2 Norm und ist Teil der Bibliothek **adapter::events::unidirectional::timers**.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| **REQ** | Event | Service Anforderung – startet den Impuls. |
| **R**   | Event | Reset – beendet den Impuls vorzeitig. |

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge. Die Ausgabe erfolgt über den Adapter **Q** (siehe unten).

### **Daten-Eingänge**
Keine direkten Dateneingänge. Die Impulszeit wird über den Adapter **PT** bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Der Impulszustand wird über den Adapter **Q** abgefragt.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **PT**  | Socket   | `adapter::types::unidirectional::ATM` | Liefert die Impulsdauer als Zeitwert. |
| **Q**   | Plug     | `adapter::types::unidirectional::AX` | Gibt den Impulsstatus aus: **D1** = aktueller Wert (TRUE während des Impulses); **E1** = Ereignis bei Impulsende oder -wechsel. |

## Funktionsweise
Der Baustein realisiert das Verhalten eines nicht nachtriggerbaren Impulsgebers (E_PULSE). Beim Eintreffen des Ereignisses **REQ** wird ein Impuls gestartet, dessen Dauer durch den am Adapter **PT** anliegenden Wert bestimmt wird. Während des Impulses ist der Ausgang **Q.D1** = *TRUE*. Nach Ablauf der Impulszeit geht **Q.D1** auf *FALSE* und das Ereignis **Q.E1** wird ausgelöst. Ein erneutes **REQ** während eines laufenden Impulses wird ignoriert (non‑retriggerable). Über den Reset‑Eingang **R** kann der Impuls jederzeit vorzeitig beendet werden; auch dann wird **Q.E1** ausgelöst.

## Technische Besonderheiten
- **Adapter‑basierte Kommunikation:** Statt direkter Daten‑/Event‑Ports werden typisierte Adapter (ATM für Zeit, AX für Ausgabe) verwendet. Dies vereinfacht die Wiederverwendung in modularen Systemen.
- **Nicht nachtriggerbar:** Ein zweiter Startimpuls während des laufenden Impulses hat keine Wirkung.
- **Validierte Versionen:** Der Baustein wurde mehrfach überarbeitet (Versionen 1.0 bis 3.0, zuletzt 2025) und enthält eine Reset‑Funktionalität.
- **Lizenziert unter EPL 2.0** (Eclipse Public License 2.0).

## Zustandsübersicht
1. **Idle** – Kein Impuls aktiv. **Q.D1** = FALSE.
2. **PulseActive** – Impuls läuft. **Q.D1** = TRUE. Wird durch **REQ** betreten und entweder durch Zeitablauf oder **R** verlassen.
   - Bei Zeitablauf: Übergang zu Idle, Auslösen von **Q.E1**.
   - Bei **R**: Übergang zu Idle, Auslösen von **Q.E1**.
3. Während **PulseActive** wird **REQ** ignoriert.

## Anwendungsszenarien
- Steuerung von Aktoren (z. B. Ventile, Lampen) mit definierter Einschaltdauer.
- Zeitgeber in Produktionsmaschinen, die einmalige Impulse benötigen.
- Signalaufbereitung in Sensor‑Aktor‑Netzwerken (AX‑/ATM‑kompatible Peripherie).

## Vergleich mit ähnlichen Bausteinen
- **E_PULSE (iec61499::events::timers):** Standard-Implementierung ohne Adapter-Schnittstelle. ATM_AX_PULSE kapselt diesen Funktionsblock und fügt die Adapter‑Anbindung hinzu.
- **ATM_AX_PULSE_R (retriggerable):** Nachtriggerbare Variante; ein erneuter **REQ** verlängert den Impuls. Der vorliegende Baustein ist nicht nachtriggerbar.
- **E_DELAY, E_CYCLE:** Andere Zeitverhalten (Verzögerung, periodisch) – nicht vergleichbar.

## Fazit
Der **ATM_AX_PULSE** ist ein robuster, nicht nachtriggerbarer Impulsbaustein, der durch seine Adapter‑Schnittstelle besonders gut in modulare Automatisierungslösungen mit AX/ATM‑Protokoll integriert werden kann. Er bietet eine klare, zuverlässige Funktionalität zur Erzeugung zeitdefinierter Impulse und erfüllt die Anforderungen der IEC 61499‑2.