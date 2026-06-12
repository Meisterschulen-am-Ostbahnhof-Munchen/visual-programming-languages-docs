# Q_ObjHideShow_AB


![Q_ObjHideShow_AB](./Q_ObjHideShow_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **Q_ObjHideShow_AB** dient als Wrapper für den Baustein `Q_ObjHideShow` und ermöglicht das Verstecken bzw. Anzeigen eines Objekts über einen **AB-Adapter** (unidirektional, BYTE). Er kapselt die direkte Ansteuerung des internen FB und stellt eine adapterbasierte Schnittstelle zur Verfügung, die eine lose Kopplung in der Anwendung fördert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | mit Variablen | Kommentar |
|---|---|---|
| `INIT` | `u16ObjId` | Service Initialization; Objekt-ID wird übergeben |

### **Ereignis-Ausgänge**
| Ereignis | Kommentar |
|---|---|
| `INITO` | Initialisierung bestätigt |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|---|---|---|
| `u16ObjId` | UINT | Objekt-ID (Object ID) |

### **Daten-Ausgänge**
Keine expliziten Datenausgänge auf FB-Ebene. Die Ausgangsdaten werden über den Adapter `qOldVisible` bereitgestellt.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|---|---|---|---|
| Socket (Eingang) | `qVisible` | `adapter::types::unidirectional::AB` | Sollwert der Sichtbarkeit: 0 = versteckt, 1 = angezeigt |
| Plug (Ausgang) | `qOldVisible` | `adapter::types::unidirectional::AB` | Alter Wert der Sichtbarkeit: 0 = versteckt, 1 = angezeigt, 0xFF = undefiniert |

## Funktionsweise
1. **Initialisierung**  
   Durch ein Ereignis am Eingang `INIT` wird der interne FB `Q_ObjHideShow` initialisiert. Die übergebene `u16ObjId` identifiziert das zu steuernde Objekt. Nach erfolgreichem Start wird das Ereignis `INITO` ausgegeben.

2. **Steuerung der Sichtbarkeit**  
   Sobald am Socket-Adapter `qVisible` ein Ereignis (E1) eintrifft, wird der zugehörige Datenwert (D1) ausgelesen und an den internen FB weitergeleitet. Der interne FB setzt daraufhin die Sichtbarkeit des Objekts entsprechend (0 = versteckt, 1 = angezeigt).

3. **Rückmeldung**  
   Nach Ausführung der Aktion sendet der interne FB das Ereignis `CNF` an den Plug-Adapter `qOldVisible`. Der alte Sichtbarkeitszustand wird als Datenwert (D1) auf `qOldVisible` bereitgestellt. So kann die aufrufende Komponente den vorherigen Zustand abfragen.

## Technische Besonderheiten
- **Wrapper-Konzept**: Der FB kapselt die direkte Verwendung von `Q_ObjHideShow` und ersetzt die lose Ereignis-/Datenverbindung durch standardisierte AB-Adapter, was eine modulare und wiederverwendbare Anbindung ermöglicht.
- **AB-Adapter (unidirektional, BYTE)**: Die Kommunikation erfolgt über einen unidirektionalen Adapter, der jeweils nur ein Ereignis und ein zugehöriges Byte überträgt. Dies vereinfacht die Einbindung in Adapter-basierte Architekturen.
- **Zustandserhaltung**: Der interne FB speichert den letzten Sichtbarkeitszustand; bei jedem neuen Befehl wird der alte Zustand am Ausgangsadapter zurückgemeldet.
- **Undefinierter Wert (0xFF)**: Der Ausgang `qOldVisible` kann den Wert 0xFF liefern, falls der vorherige Zustand nicht bekannt ist (z. B. nach Neustart ohne vorherige Initialisierung).

## Zustandsübersicht
Der FB selbst besitzt keinen eigenen Zustandsautomaten. Sein Verhalten wird vollständig durch den eingebetteten Baustein `Q_ObjHideShow` bestimmt. Grundsätzlich gilt:

- **Nach INIT**: FB ist betriebsbereit und wartet auf Ereignisse vom Socket-Adapter `qVisible`.
- **Bei jedem eingehenden Socket-Ereignis**: Sichtbarkeit wird gesetzt und das Ergebnis über den Plug-Adapter zurückgemeldet.

## Anwendungsszenarien
- **Visualisierungssteuerung**: Ein- und Ausblenden grafischer Objekte (z. B. in HMI-Systemen) basierend auf binären oder numerischen Steuerwerten.
- **Zustandsrückmeldung**: Überwachung von Sichtbarkeitsänderungen; die alte Sichtbarkeit kann für Logikentscheidungen oder Protokollierung genutzt werden.
- **Adapter-basierte Automatisierung**: Einbindung in ein System, das auf Adapter-Schnittstellen setzt, um Austauschbarkeit und Entkopplung zu erreichen.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaften |
|---|---|
| `Q_ObjHideShow` (direkt) | Ereignis-/Daten-Schnittstelle ohne Adapter; direkte Verschaltung erforderlich |
| `Q_ObjHideShow_AB` (dieser FB) | Nutzt AB-Adapter für lose Kopplung; einfachere Integration in adapterbasierte Netzwerke |
| Andere AB-basierte Wrapper | Ähnliches Konzept für andere Befehle (z. B. `Q_ObjMove_AB`), jedoch spezifisch auf Sichtbarkeit ausgelegt |

Der wesentliche Vorteil des Wrappers liegt in der Anpassung an die AB-Adapter‑Schnittstelle, ohne die eigentliche Funktionalität zu verändern.

## Fazit
Der Funktionsblock `Q_ObjHideShow_AB` stellt eine adapterbasierte, wiederverwendbare Komponente zur Steuerung der Sichtbarkeit von Objekten dar. Durch die Kapselung des internen FB und die Nutzung unidirektionaler AB-Adapter wird eine saubere Trennung von Steuerlogik und Ausführung erreicht. Er eignet sich besonders für modulare Automatisierungslösungen, die auf lose Kopplung und standardisierte Schnittstellen angewiesen sind.