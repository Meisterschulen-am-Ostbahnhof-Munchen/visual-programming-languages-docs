# AX_FB_TON_LTIME


![AX_FB_TON_LTIME](./AX_FB_TON_LTIME.svg)

* * * * * * * * * *

## Einleitung  
Der Baustein **AX_FB_TON_LTIME** realisiert eine Einschaltverzögerung (On-Delay Timer) nach IEC 61131-3 mit dem Datentyp `LTIME` und integriertem **AX‑Adapter** Interface. Er eignet sich besonders für zeitkritische Steuerungsaufgaben, bei denen sowohl Ereignisse als auch Daten über standardisierte Adapter ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**  
| Name | Typ | Beschreibung |
|------|-----|-------------|
| REQ | `Event` | Normaler Ausführungsanstoß (nicht flankengetriggert); startet die Zeitmessung, wenn das Signal am Dateneingang `IN` oder am Adapter `IN.E1` aktiv ist. |

### **Ereignis-Ausgänge**  
| Name | Typ | Beschreibung |
|------|-----|-------------|
| CNF | `Event` | Bestätigung der Ausführung. Wird ausgelöst, sobald der Timer abläuft oder die Bedingung erfüllt ist. |

### **Daten-Eingänge**  
| Name | Typ | Beschreibung |
|------|-----|-------------|
| PT | `LTIME` | Vorgabezeit (Preset Time) für die Einschaltverzögerung. |

### **Daten-Ausgänge**  
| Name | Typ | Beschreibung |
|------|-----|-------------|
| ET | `LTIME` | Abgelaufene Zeit (Elapsed Time) seit dem Start der Zeitmessung. |

### **Adapter**  
| Typ | Richtung | Beschreibung |
|-----|----------|-------------|
| `IN` | Socket (Input) | Unidirektionaler AX‑Adapter für Eingangsdaten. Enthält ein Ereignis (`E1`) und einen Datenwert (`D1`). Das Ereignis startet die Zeitmessung; der Datenwert bestimmt den Timer‑Eingang (`IN`). |
| `Q` | Plug (Output) | Unidirektionaler AX‑Adapter für Ausgangsdaten. Gibt das Ergebnis der Zeitprüfung aus: `1`, wenn die abgelaufene Zeit die Vorgabezeit erreicht hat, sonst `0`. |

## Funktionsweise  
Der Baustein ist als Composite realisiert und enthält intern den IEC‑61131‑3 Timer **FB_TON_LTIME** sowie ein flankengesteuertes D‑Flip‑Flop (**E_D_FF**).  

- **Startbedingungen**: Die Zeitmessung wird gestartet, sobald ein Ereignis am Adapter `IN.E1` oder am Ereigniseingang `REQ` eintrifft. Gleichzeitig muss der Datenwert `IN.D1` (oder der interne Timer‑Eingang) auf `TRUE` gesetzt sein.  
- **Ablauf**: Der interne Timer zählt die Zeit hoch. Der Ausgang `ET` gibt die aktuell abgelaufene Zeit aus.  
- **Ende**: Wenn die abgelaufene Zeit `ET` die Vorgabezeit `PT` erreicht, wird der Timer‑Ausgang (`Q`) auf `TRUE` gesetzt. Dies löst das Ereignis `CNF` aus und taktet das D‑Flip‑Flop.  
- **Ausgangsadapter**: Das D‑Flip‑Flop speichert den Zustand und gibt ihn über den Adapter `Q.D1` aus. Das Ereignis `Q.E1` signalisiert die Ausgangsänderung.

## Technische Besonderheiten  
- **LTIME‑Datentyp**: Ermöglicht eine sehr hohe Zeitauflösung (Nanosekundenbereich) und große Zeitbereiche.  
- **Adapter‑Schnittstelle**: Der Baustein kann über standardisierte AX‑Adapter in bestehende Systeme eingebunden werden, ohne direkte Ereignis‑ oder Datenverbindungen zu benötigen.  
- **Flankengetriggerte Ausgabe**: Durch das interne D‑Flip‑Flop wird der Ausgangszustand erst bei einer positiven Flanke des Timer‑Abschlusses aktualisiert – dies vermeidet unerwünschtes Flattern.  
- **Internes Netzwerk**: Die Funktionalität wird durch die Kombination von Standard‑Bausteinen erreicht, was die Implementierung transparent und testbar macht.

## Zustandsübersicht  
Der Baustein selbst besitzt kein eigenes Zustandsdiagramm, da er aus einem internen FBNetzwerk besteht. Das Verhalten kann aber aus dem zugrunde liegenden IEC‑Timer‑Baustein abgeleitet werden:

1. **Inaktiv** – Timer läuft nicht, `ET` = 0, Ausgang `Q` = `FALSE`.  
2. **Zeit läuft** – Eingang `IN` = `TRUE`, Timer zählt `ET` hoch.  
3. **Abgelaufen** – `ET` ≥ `PT`; `Q` wechselt auf `TRUE` und bleibt, bis `IN` auf `FALSE` fällt oder ein erneuter REQ die Zeitmessung zurücksetzt.

## Anwendungsszenarien  
- **Verzögerte Einschaltung von Aktoren**: Ein Ventil oder Motor soll erst nach einer definierten Verzögerungszeit eingeschaltet werden.  
- **Synchronisation von Prozessen**: Warten auf das Eintreffen eines Signals über den Adapter, bevor eine zeitkritische Aktion ausgelöst wird.  
- **Überwachung von Reaktionszeiten**: Erfassen der verstrichenen Zeit zwischen einem Ereignis und einer bestimmten Bedingung.  
- **Erweiterung bestehender AX‑basierter Systeme**: Austausch von Standard‑Timerbausteinen durch die Adapter‑Variante ohne Änderung der übergeordneten Struktur.

## Vergleich mit ähnlichen Bausteinen  
- **FB_TON_LTIME** (reiner IEC‑Timer): Besitzt keine Adapter, benötigt direkte Ereignis‑ und Datenverbindungen. Der AX_FB_TON_LTIME erweitert diesen um eine standardisierte, leicht koppelbare Schnittstelle.  
- **Ereignisgesteuerte Timer** (z.B. E_TON): Arbeiten oft mit Booleschen Eingängen und besitzen keine native LTIME‑Unterstützung. Der hier vorgestellte Baustein kombiniert präzise Langzeitmessung mit einer flexiblen Adapter‑Anbindung.

## Fazit  
Der **AX_FB_TON_LTIME** ist ein leistungsfähiger, adapterbasierter Einschaltverzögerungs‑Baustein für die IEC‑61499‑Umgebung. Er vereint die Vorteile des standardisierten IEC‑61131‑3‑Timers (LTIME, exakte Zeitmessung) mit der Modularität und Wiederverwendbarkeit von AX‑Adaptern. Durch die interne Kombination mit einem D‑Flip‑Flop wird eine zuverlässige, flankengetriggerte Ausgabe gewährleistet. Er eignet sich ideal für zeitkritische Steuerungen, die in ein Adapter‑basiertes Architekturmodell eingebettet sind.