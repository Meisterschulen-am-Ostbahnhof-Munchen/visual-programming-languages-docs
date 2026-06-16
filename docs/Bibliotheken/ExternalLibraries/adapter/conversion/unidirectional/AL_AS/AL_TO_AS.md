# AL_TO_AS


![AL_TO_AS](./AL_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AL_TO_AS** ist ein Composite-Baustein, der einen unidirektionalen AL-Adapter (Daten vom Typ LWORD) in einen unidirektionalen AS-Adapter (Daten vom Typ SINT) umwandelt. Er ermöglicht die nahtlose Integration von Komponenten, die mit unterschiedlichen Datentypen arbeiten, indem er die Signale konvertiert und über die jeweiligen Adapter-Schnittstellen weiterreicht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| Socket | AL_IN | Input | Unidirektionaler AL-Adapter, der LWORD-Daten bereitstellt. |
| Plug   | AS_OUT | Output | Unidirektionaler AS-Adapter, der die konvertierten SINT-Daten ausgibt. |

## Funktionsweise
Der FB empfängt über den Socket `AL_IN` Ereignisse und LWORD-Daten. Intern wird ein Baustein vom Typ `F_LWORD_TO_SINT` (aus der IEC-61131-Bibliothek) verwendet, um die Eingangsdaten (LWORD) in den Ausgangsdatentyp SINT zu konvertieren. Die Ereignissteuerung erfolgt wie folgt:
- Ein eingehendes Ereignis am Socket `AL_IN.E1` löst den Eingang `REQ` des internen Konvertierungsbausteins aus.
- Nach erfolgreicher Konvertierung signalisiert der Ausgang `CNF` des Konverters ein Ereignis, das an den Plug `AS_OUT.E1` weitergegeben wird.
- Gleichzeitig wird der konvertierte Datenwert vom Ausgang `OUT` des Konverters an den Datenausgang `AS_OUT.D1` übergeben.

Der gesamte Ablauf ist ereignisgesteuert: Nur bei einem Ereignis am `AL_IN` wird die Konvertierung durchgeführt und ein Ereignis am `AS_OUT` ausgelöst.

## Technische Besonderheiten
- Der FB ist als Composite implementiert und nutzt die vordefinierte Konvertierungsfunktion `F_LWORD_TO_SINT`, was eine hohe Wiederverwendbarkeit und Standardkonformität gewährleistet.
- Die Konvertierung erfolgt **unidirektional** nur von LWORD zu SINT; eine Rückrichtung ist nicht vorgesehen.
- Die Ereignisweiterleitung ist direkt: Ein Ereignis am Eingang führt zu genau einem Ereignis am Ausgang.
- Die Datenbreite reduziert sich von 64 Bit (LWORD) auf 8 Bit (SINT), daher sind nur Werte im Bereich [-128, 127] darstellbar. Bei Überschreitung dieses Bereichs verhält sich der interne Konverter entsprechend der IEC-61131-Definition (z. B. Überlaufkennzeichnung oder Modulo-Verhalten).

## Zustandsübersicht
Der FB besitzt keinen eigenen Zustandsautomaten. Sein Verhalten ist rein kombinatorisch mit ereignisgesteuerter Triggerung. Ein interner Zustand existiert nicht; die Konvertierung erfolgt immer auf Basis der aktuellen Eingangsdaten bei einem Ereignis.

## Anwendungsszenarien
- **Systemintegration**: Wenn ein Softwaresystem oder ein Gerät LWORD-Schnittstellen (Adapter AL) verwendet, aber ein anderer Teil des Systems nur AS-Adapter (SINT) unterstützt, kann dieser FB als Brücke dienen.
- **Datenreduktion**: Gezieltes Umwandeln von 64‑Bit-Daten in einen 8‑Bit-Wert, z. B. für die Übergabe an einfache Aktoren oder Anzeigen, die nur SINT verarbeiten.
- **Protokollanpassung**: In heterogenen Automatisierungsnetzwerken, in denen unterschiedliche Adaptertypen (unidirektional) zum Einsatz kommen, vereinfacht dieser FB die Konvertierung auf einer einzigen logischen Ebene.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingangstyp | Ausgangstyp | Besonderheit |
|----------|-------------|-------------|--------------|
| **AL_TO_AS** | LWORD (Adapter) | SINT (Adapter) | Composite; verwendet `F_LWORD_TO_SINT` |
| `F_LWORD_TO_SINT` | LWORD (Daten) | SINT (Daten) | Reiner Datenkonverter, keine Adaptereinbindung |
| `F_LWORD_TO_DINT` | LWORD | DINT | Konvertierung zu 32‑Bit-Integer |
| `F_SINT_TO_LWORD` | SINT | LWORD | Rückrichtung (sofern vorhanden) |

Der **AL_TO_AS** hebt sich durch seine Adapter‑zu‑Adapter‑Schnittstelle ab, die eine direkte Verbindung zwischen zwei unterschiedlichen Adaptertypen ohne zusätzliche manuelle Verkabelung von Einzelereignissen und Daten ermöglicht.

## Fazit
Der **AL_TO_AS**‑Funktionsblock ist ein praktischer, standardkonformer Konverterbaustein für unidirektionale Adapter. Er kapselt die notwendige Typumwandlung von LWORD nach SINT und vereinfacht die Integration in bestehende 4diac‑Projekte. Aufgrund seiner Composite‑Struktur und der Verwendung einer etablierten Konvertierungsfunktion ist er zuverlässig, leicht verständlich und erweiterbar. Er eignet sich besonders für Szenarien, in denen Datenbreiten reduziert oder Schnittstellen angepasst werden müssen.