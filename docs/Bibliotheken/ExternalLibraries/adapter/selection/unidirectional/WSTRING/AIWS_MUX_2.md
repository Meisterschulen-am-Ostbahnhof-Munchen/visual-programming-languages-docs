# AIWS_MUX_2


![AIWS_MUX_2](./AIWS_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der AIWS_MUX_2 ist ein generischer Multiplexer für den AIWS-Adapter. Er ermöglicht die Auswahl zwischen zwei AIWS-Eingangssignalen (IN1, IN2) und leitet das gewählte Signal an den Ausgang (OUT) weiter. Die Selektion wird über einen Index K ereignisgesteuert ausgelöst.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung | Mit-Variablen |
|----------|--------------|---------------|
| REQ      | Ereignis zur Auslösung der Indexsetzung | K |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der Selektion |

### **Daten-Eingänge**
| Variable | Typ  | Beschreibung |
|----------|------|--------------|
| K        | UINT | Index für die Auswahl (0 = IN1, 1 = IN2) |

### **Daten-Ausgänge**
Keine (die Signalübergabe erfolgt ausschließlich über Adapter).

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Plug (Ausgang) | OUT | AIWS | Ausgangssignal, liefert das ausgewählte AIWS-Signal |
| Socket (Eingang) | IN1 | AIWS | Erster AIWS-Eingang (Auswahl bei K=0) |
| Socket (Eingang) | IN2 | AIWS | Zweiter AIWS-Eingang (Auswahl bei K=1) |

## Funktionsweise
Bei einem Ereignis am **REQ**-Eingang wird der aktuelle Wert des Index **K** ausgewertet:
- Ist **K = 0**, wird das Signal von **IN1** auf **OUT** durchgeschaltet.
- Ist **K = 1**, wird das Signal von **IN2** auf **OUT** durchgeschaltet.

Nach erfolgreicher Selektion wird das Ereignis **CNF** ausgegeben. Der Baustein arbeitet ereignisgesteuert und führt keine kontinuierliche Aktualisierung der Out-Adapterwerte durch.

## Technische Besonderheiten
- **Generischer Funktionsblock**: Der tatsächliche Klassenname lautet `GEN_AIWS_MUX` (hinterlegt im Attribut `eclipse4diac::core::GenericClassName`). Dadurch kann der Baustein in verschiedenen Ausprägungen (z. B. generiert für unterschiedliche Adaptertypen) eingesetzt werden.
- **Adaptertechnologie**: Der Baustein verwendet unidirektionale AIWS-Adapter (Eclipse 4diac). Die Schnittstelle ist rein adapterbasiert; es werden keine Einzelvariablen für die analogen Werte genutzt.
- **Copyright**: Erstellt von Franz Höpfinger für die HR Agrartechnik GmbH (Version 1.0, 2026-05-28) unter der EPL‑2.0-Lizenz.
- **Kompilierung**: Nutzt das Importpaket `eclipse4diac::core::TypeHash`.

## Zustandsübersicht
Der Baustein enthält keine explizite Zustandsmaschine (ECC) in der XML-Beschreibung. Das implizite Verhalten lässt sich wie folgt beschreiben:
1. **Ruhezustand** (idle) – es liegt kein REQ-Ereignis an.
2. Bei REQ erfolgt die Auswertung von K und die sofortige Umschaltung.
3. Danach wird CNF gesendet und der Baustein kehrt in den Ruhezustand zurück.

Mehrere REQ-Ereignisse nacheinander sind möglich; eine laufende Verarbeitung wird nicht blockiert.

## Anwendungsszenarien
- **Sensorumschaltung**: Auswahl zwischen zwei analogen Messwerten (z. B. Temperatur oder Druck) in einer Automatisierungssteuerung.
- **Betriebsartenwechsel**: Umschaltung zwischen zwei verschiedenen Signalquellen, wie unterschiedlichen Messstellen oder redundanten Sensoren.
- **Test- und Simulationsumgebungen**: Einfaches Wechseln des zu analysierenden AIWS-Signals.

## Vergleich mit ähnlichen Bausteinen
- **AIWS_MUX_4** (wenn vorhanden): Bietet vier statt zwei Eingänge, benötigt mehr Indexbits.
- **Standard‑Multiplexer (Daten‑MUX)**: Arbeitet meist mit einzelnen Basisvariablen (z. B. INT, REAL) und ohne Adapter. Der AIWS_MUX_2 kapselt dagegen komplexe Signalstrukturen in einem Adapter, was die Wiederverwendung und Reduzierung der Verdrahtung auf FB-Ebene vereinfacht.
- **Ereignisgesteuerte vs. kontinuierliche MUX**: Der Baustein aktualisiert nur bei REQ, was in vielen Anwendungen ausreicht und Ressourcen spart.

## Fazit
Der AIWS_MUX_2 ist ein kompakter, generischer Multiplexer für AIWS-Adapter. Durch die einfache ereignisgesteuerte Selektion auf Basis eines Index eignet er sich ideal für die Umschaltung zwischen zwei analogen Signalen. Die Nutzung der Eclipse‑4diac‑Adaptertechnologie sorgt für eine saubere, wiederverwendbare Schnittstelle und erleichtert die Integration in komplexe Automatisierungslösungen.