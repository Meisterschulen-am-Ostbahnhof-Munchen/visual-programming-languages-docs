# UDINT_AUDI_AX_SEL_AUDI


![UDINT_AUDI_AX_SEL_AUDI](./UDINT_AUDI_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `UDINT_AUDI_AX_SEL_AUDI` dient der binären Auswahl (Multiplexing) zwischen zwei Eingangswerten des Datentyps `UDINT`. Die Besonderheit dieses Bausteins liegt in der Nutzung von standardisierten Adapter-Schnittstellen zur Signalübertragung. Er ermöglicht es, entweder einen direkt anliegenden `UDINT`-Wert oder einen über einen Adapter bereitgestellten Wert basierend auf einem Selektionssignal auszuwählen und das Ergebnis über einen Ausgangs-Adapter weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI0** | Signalisiert die Aktualisierung des direkt am Baustein anliegenden Eingangswerts `IN0`. | `IN0` |

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung erfolgt über die Adapter-Schnittstellen.*

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | UDINT | Direkt am Baustein anliegender, auswählbarer Eingangswert. |

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden. Die Datenübergabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

| Adapter-Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::AUDI` | Plug | Der ausgewählte Ausgangswert (UDINT) inkl. zugehörigem Ereignis. |
| **IN1** | `adapter::types::unidirectional::AUDI` | Socket | Der zweite auswählbare Eingangswert, der über diesen Adapter empfangen wird. |
| **G** | `adapter::types::unidirectional::AX` | Socket | Das Auswahlsignal (Selector), das bestimmt, welcher Eingang auf den Ausgang geschaltet wird. |

## Funktionsweise

Der Baustein realisiert ein internes logisches Netzwerk zur daten- und ereignisgesteuerten Selektion:

1. **Signalpufferung**: 
   Die Eingänge `IN0`, `IN1` (über Adapter) und das Auswahlsignal `G` (über Adapter) werden intern durch flankengetriggerte Flipflops (`E_D_FF` bzw. `E_D_FF_ANY`) gepuffert. Dies stellt sicher, dass Werteänderungen und Ereignisse synchron verarbeitet werden.
2. **Datenübertragung**:
   Die gepufferten Eingangswerte werden über Zuweisungsbausteine (`F_MOVE`) für den Datentyp `UDINT` an den zentralen Selektionsbaustein weitergeleitet.
3. **Auswahl-Logik (`F_SEL`)**:
   - Wenn das Auswahlsignal `G` (über Adapter `G.D1`) den Zustand **FALSE** hat, wird der Wert von **IN0** an den Ausgang durchgeschaltet.
   - Wenn das Auswahlsignal `G` den Zustand **TRUE** hat, wird der Wert des Adapters **IN1** (über `IN1.D1`) ausgewählt.
4. **Ausgabe**:
   Das Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben und triggert dort das entsprechende Ausgangsereignis (`OUT.E1`).

Anpassungen an einem der Eingänge (`IN0`, `IN1`) oder eine Änderung des Selektors (`G`) führen sofort zu einer Neuberechnung und Aktualisierung des Ausgangs.

## Technische Besonderheiten

- **Adapter-Integration**: Der Baustein nutzt unidirektionale Adaptertypen (`AUDI` für UDINT-Signale, `AX` für Selektionssignale), um die Verdrahtung in komplexen Systemen zu vereinfachen und modulare Architekturen zu unterstützen.
- **Ereigniskonsistenz**: Durch den Einsatz von internen `E_D_FF_ANY`-Bausteinen wird sichergestellt, dass Datenwerte immer konsistent mit ihren zugehörigen Ereignissen übertragen werden und keine unvollständigen Datenzustände am Ausgang ankommen.

## Zustandsübersicht

Da es sich um ein Netzwerk aus zusammengesetzten Funktionsbausteinen (Composite FB Network) handelt, besitzt der Baustein keine eigene klassische Zustandsmaschine (ECC). Der Daten- und Ereignisfluss wird durch die internen Verbindungen bestimmt:

- Jedes Ereignis an `EI0`, `IN1.E1` oder `G.E1` stößt die interne Verarbeitungskette an.
- Nach erfolgreicher Selektion wird immer das Ereignis `OUT.E1` des Ausgangs-Plugs ausgelöst.

## Anwendungsszenarien

- **Sollwertumschaltung**: Umschalten zwischen einem lokal vorgegebenen Standardwert (`IN0`) und einem dynamisch von einem übergeordneten System gelieferten Wert (`IN1`).
- **Betriebsmodi-Umschaltung**: Auswahl verschiedener numerischer Parameter (z.B. Geschwindigkeiten, Zählergrenzen) in Abhängigkeit von einem binären Zustandssignal.
- **Modulare Anlagensteuerungen**: Kopplung verteilter Steuerungskomponenten über standardisierte Adapterschnittstellen zur Reduzierung von Signalverbindungen im Systemmodell.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` (nach IEC 61131-3) bietet dieser Funktionsbaustein eine direkte Integration von IEC 61499-Adaptern. Während beim Standard-`F_SEL` alle Ereignisse und Daten manuell verdrahtet werden müssen, kapselt dieser Baustein die Ereignissynchronisation und Adapterkopplung, was den Engineering-Aufwand bei komplexen Projekten erheblich reduziert.

## Fazit

Der `UDINT_AUDI_AX_SEL_AUDI` ist ein spezialisierter und zuverlässiger Multiplexer für 32-Bit-Ganzzahlen ohne Vorzeichen (UDINT). Er eignet sich hervorragend für moderne, serviceorientierte und ereignisgesteuerte Automatisierungsanwendungen, bei denen eine saubere Kapselung von Signalen über Adapter gefordert ist.