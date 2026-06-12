# Q_ObjEnableDisable_AX


![Q_ObjEnableDisable_AX](./Q_ObjEnableDisable_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **Q_ObjEnableDisable_AX** ist ein Composite-Baustein, der als Adapter-Wrapper für den internen Baustein `Q_ObjEnableDisable` dient. Er ermöglicht die Ansteuerung eines Enable/Disable-Befehls (BOOL) über einen unidirektionalen AX-Adapter (Socket) und gibt den vorherigen Zustand über einen AB-Adapter (Plug) zurück. Der Baustein wird typischerweise in ISOBUS-basierten Steuerungssystemen eingesetzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `INIT` | EInit | Initialisierung des Bausteins; übergeben wird die Objekt-ID (u16ObjId). |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `INITO` | EInit | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `u16ObjId` | UINT | Objekt-ID, die beim INIT-Ereignis gesetzt wird. |

### **Daten-Ausgänge**
Keine direkten Datenausgänge; der alte Zustand wird über den Adapter-Plug `qOldAbility` ausgegeben.

### **Adapter**
| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `qAbility` | `adapter::types::unidirectional::AX` | Socket | Empfängt den Enable/Disable-Befehl (0 = disable, 1 = enable, 0xFF = undefined). |
| `qOldAbility` | `adapter::types::unidirectional::AB` | Plug | Gibt den vorherigen Zustand des Objekts zurück (gleiche Codierung). |

## Funktionsweise
1. **Initialisierung**  
   Ein INIT-Ereignis am Eingang `INIT` setzt die gewünschte Objekt-ID (`u16ObjId`) und initialisiert den internen Baustein `Q_ObjEnableDisable`. Nach erfolgreicher Initialisierung wird das Ereignis `INITO` ausgegeben.

2. **Signalverarbeitung**  
   - Ein neuer Befehl wird über den Socket-Adapter `qAbility` empfangen:  
     - Das Ereignis `E1` des Adapters löst den REQ-Eingang des internen Bausteins aus.  
     - Die Daten `D1` (0/1/0xFF) werden auf den Eingang `qAbility` des internen Bausteins weitergeleitet.  
   - Der interne Baustein verarbeitet den Befehl, aktiviert oder deaktiviert das Objekt mit der gegebenen ID und gibt den vorherigen Zustand aus.  
   - Die Bestätigung `CNF` des internen Bausteins wird auf das Ereignis `E1` des Plug-Adapters `qOldAbility` übertragen.  
   - Der vorherige Zustand wird über den Datenausgang `D1` des Plug-Adapters bereitgestellt.

3. **Ausgabe alter Zustand**  
   Der Adapter-Plug `qOldAbility` stellt den Zustand vor der letzten Änderung als BOOL-Wert (0/1/0xFF) zur Verfügung. Die Ereignisverbindung stellt sicher, dass das Ausgangseignis zeitlich korrekt erfolgt.

## Technische Besonderheiten
- Der Baustein kapselt die Logik des komplexeren `Q_ObjEnableDisable` und bietet eine vereinfachte Schnittstelle über zwei standardisierte Adapter (AX/AB).  
- Adapter-Socket `qAbility` erwartet unidirektionale Kommunikation (nur Wertübergabe), Adapter-Plug `qOldAbility` gibt das Ergebnis zurück.  
- Die Objekt-ID wird nur bei INIT gesetzt; ein Wechsel der ID während des Betriebs ist nicht vorgesehen.

## Zustandsübersicht
Der FB `Q_ObjEnableDisable_AX` selbst besitzt keinen eigenen Zustandsautomaten. Die interne Zustandslogik wird vom enthaltenen Baustein `Q_ObjEnableDisable` realisiert. Dessen typische Zustände sind:
- **IDLE** – Warten auf einen Befehl (REQ).  
- **Processing** – Verarbeitung des Befehls (z. B. Senden einer CAN-Nachricht).  
- **Done** – Befehl abgeschlossen, Ausgabe des alten Zustands und Rücksprung nach IDLE.

## Anwendungsszenarien
- **ISOBUS-Steuerung**: Aktivieren/Deaktivieren eines landwirtschaftlichen Geräts (z. B. Ventil, Beleuchtung) basierend auf einem booleschen Signal eines AX-Adapters.  
- **Universaladapter**: Einbindung von Enable/Disable-Funktionen in Systeme, die standardisierte unidirektionale Adapter verwenden.  
- **Zustandsrückmeldung**: Erfassung des vorherigen Zustands für Diagnose- oder Überwachungszwecke.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Schnittstelle | Besonderheit |
|----------|---------------|--------------|
| **Q_ObjEnableDisable** | Direkte Ereignis-/Dateneingänge | Erfordert separate Bool-Eingänge und Ereignisse. |
| **Q_ObjEnableDisable_AX** | AX/AB-Adapter | Einfache Integration in Adapter-basierte Architekturen; reduziert Verdrahtungsaufwand. |

Der AX-Wrapper fügt keine neue Funktionalität hinzu, sondern optimiert die Anbindung an bestehende Adapter-Kommunikation.

## Fazit
Der Funktionsblock **Q_ObjEnableDisable_AX** ist ein praktischer Adapter-Wrapper, der die Steuerung eines ISOBUS-Objekts mittels Enable/Disable-Befehlen über einen unidirektionalen AX-Adapter vereinfacht. Er kapselt die interne Logik, ermöglicht eine saubere Schnittstellentrennung und gibt den vorherigen Zustand über einen AB-Adapter zurück. Der Baustein eignet sich besonders für modulare Steuerungsarchitekturen, die auf standardisierten Adapter-Typen basieren.