# AUDI_MUL_4


![AUDI_MUL_4](./AUDI_MUL_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUDI_MUL_4** führt eine arithmetische Multiplikation auf Basis von vier Eingangswerten durch. Es handelt sich um einen generischen Baustein (Generic FB), der über Adapter-Schnittstellen mit einer unidirektionalen Datenstruktur vom Typ `adapter::types::unidirectional::AUDI` arbeitet. Der Baustein ist gemäß IEC 61499-2 spezifiziert und wird insbesondere in Automatisierungslösungen eingesetzt, bei denen eine skalierbare Multiplikation mehrerer Eingangsgrößen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Der Baustein verfügt über keine klassischen Dateneingänge. Alle Eingangswerte werden über Adapter-Schnittstellen bereitgestellt.

### **Daten-Ausgänge**
Der Baustein verfügt über keine klassischen Datenausgänge. Das Multiplikationsergebnis wird über einen Adapter-Plug ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|------|------|----------|-----------|
| `adapter::types::unidirectional::AUDI` | IN1 | Eingang (Socket) | MUL input 1 |
| `adapter::types::unidirectional::AUDI` | IN2 | Eingang (Socket) | MUL input 2 |
| `adapter::types::unidirectional::AUDI` | IN3 | Eingang (Socket) | MUL input 3 |
| `adapter::types::unidirectional::AUDI` | IN4 | Eingang (Socket) | MUL input 4 |
| `adapter::types::unidirectional::AUDI` | OUT | Ausgang (Plug)  | MUL result |

Der Adapter `AUDI` ist als unidirektionaler Datentyp definiert und transportiert die jeweiligen numerischen Werte sowie das Ergebnis.

## Funktionsweise
Der FB multipliziert die an den vier Adaptern **IN1**, **IN2**, **IN3** und **IN4** anliegenden Werte und stellt das Produkt am Ausgangsadapter **OUT** bereit. Die Verarbeitung erfolgt asynchron, sobald alle erforderlichen Eingangsdaten anliegen. Der Baustein ist als generischer FB ausgelegt, d.h. der verwendete Datentyp kann über das Attribut `eclipse4diac::core::GenericClassName` zur Laufzeit oder beim Deployment festgelegt werden. Standardmäßig wird der Name `'GEN_AUDI_MUL'` verwendet.

## Technische Besonderheiten
- **Generische Implementierung**: Der FB ist generisch und kann an verschiedene numerische Datentypen angepasst werden (z. B. INT, REAL, LREAL). Die Konkretisierung erfolgt über das Klassenattribut.
- **Adapterbasierte Kommunikation**: Anstelle von direkten Ein-/Ausgängen werden Adapter genutzt. Dies erlaubt eine flexible Kapselung der Daten und ermöglicht die Wiederverwendung in unterschiedlichen Kontexten.
- **Typ-Hash**: Der Attributwert `eclipse4diac::core::TypeHash` ist leer und kann zur Laufzeit durch den tatsächlichen Hash des verwendeten Datentyps ergänzt werden.
- **Keine Zustandsautomaten**: Der FB besitzt kein ECC (Ereignisgesteuerter Zustandsautomat), da die Multiplikation rein datengetrieben erfolgt.

## Zustandsübersicht
Nicht zutreffend – der Baustein arbeitet ohne Zustandsmaschine. Die Multiplikation wird durch die Verfügbarkeit der Eingangsdaten ausgelöst.

## Anwendungsszenarien
- **Prozessautomatisierung**: Multiplikation von vier analogen Messwerten (z. B. Durchfluss, Druck, Temperatur, Dichte) zur Berechnung einer Massenstromkorrektur.
- **Maschinensteuerung**: Berechnung von Gesamtlasten oder Drehmomenten aus mehreren Einzelgrößen.
- **Datenvorverarbeitung**: Skalierung oder Gewichtung von Sensordaten in einem übergeordneten Regelungssystem.
- **Bildverarbeitung**: Kombination mehrerer Kanäle (z. B. Rot, Grün, Blau, Intensität) durch Multiplikation.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu klassischen IEC‑61131-Multiplikationsbausteinen (z. B. `MUL` mit festen Datentypen) bietet `AUDI_MUL_4` eine generische, adapterbasierte Schnittstelle, die eine flexible Wiederverwendung ermöglicht. Andere Multiplikatoren wie `MUL_2` oder `AUDI_MUL_2` verarbeiten nur zwei Eingänge, während `AUDI_MUL_4` vier Eingänge gleichzeitig multipliziert. Bausteine mit ereignisgesteuerter Verarbeitung (z. B. `MUL_E`) erfordern zusätzliche Trigger, während dieser FB rein datengesteuert arbeitet.

## Fazit
Der FB **AUDI_MUL_4** ist ein spezialisierter, generischer Multiplikationsbaustein für vier Eingangswerte. Durch die Nutzung von Adaptern und die generische Auslegung eignet er sich besonders für modulare, wiederverwendbare Automatisierungslösungen, bei denen Flexibilität und Skalierbarkeit im Vordergrund stehen. Die einfache Schnittstelle ohne Ereignisse macht die Integration in datenorientierte Architekturen unkompliziert.