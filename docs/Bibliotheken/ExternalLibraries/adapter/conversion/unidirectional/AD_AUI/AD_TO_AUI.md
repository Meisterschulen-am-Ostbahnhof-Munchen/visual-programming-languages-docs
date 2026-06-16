# AD_TO_AUI


![AD_TO_AUI](./AD_TO_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AD_TO_AUI` ist ein Composite-Baustein, der einen AD-Adapter (DWORD-basiert) in einen AUI-Adapter (UINT-basiert) umwandelt. Er ermöglicht die nahtlose Integration von Komponenten, die mit unterschiedlichen Datentypen arbeiten, indem er die eingehenden DWORD-Werte in UINT-Werte konvertiert und die entsprechenden Ereignisse weiterleitet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| (keine eigenen) | - | Der FB besitzt keine eigenen Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Adapter-Socket `AD_IN`. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| (keine eigenen) | - | Der FB besitzt keine eigenen Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den Adapter-Plug `AUI_OUT`. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| (keine eigenen) | - | Alle Daten werden über den Adapter-Socket `AD_IN` bereitgestellt. |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| (keine eigenen) | - | Alle Daten werden über den Adapter-Plug `AUI_OUT` ausgegeben. |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AD` | `AD_IN` | Socket (Eingang) | Nimmt DWORD-Werte und zugehörige Ereignisse entgegen. |
| `adapter::types::unidirectional::AUI` | `AUI_OUT` | Plug (Ausgang) | Gibt konvertierte UINT-Werte und zugehörige Ereignisse aus. |

Der Adapter `AD_IN` stellt ein Ereignis `E1` und ein Daten-Element `D1` (Typ DWORD) bereit.  
Der Adapter `AUI_OUT` erwartet ein Ereignis `E1` und ein Daten-Element `D1` (Typ UINT).  
Die Zuordnung erfolgt wie in der Funktionsweise beschrieben.

## Funktionsweise
Der FB enthält eine Instanz des Standard-Konvertierungsbausteins `iec61131::conversion::F_DWORD_TO_UINT`. Die interne Verschaltung:

1. **Ereignissteuerung**:  
   - Das Ereignis `AD_IN.E1` wird direkt an den Konvertierungsbaustein (`Convert.REQ`) weitergeleitet.  
   - Nach erfolgreicher Konvertierung signalisiert `Convert.CNF` das Ereignis an `AUI_OUT.E1`.

2. **Datenfluss**:  
   - Der Datenwert `AD_IN.D1` (DWORD) wird an den Eingang `Convert.IN` übergeben.  
   - Der Ausgang `Convert.OUT` liefert den umgewandelten Wert (UINT) an `AUI_OUT.D1`.

Der FB führt somit eine ereignisgesteuerte, unidirektionale Typkonvertierung von DWORD nach UINT durch. Die Wandlung erfolgt nach der IEC 61131-3 Standardfunktion `DWORD_TO_UINT`.

## Technische Besonderheiten
- **Composite-Baustein**: Der FB kapselt einen bereits bestehenden Standard-Konvertierungsbaustein und zwei Adapter-Schnittstellen. Dies vereinfacht die Wiederverwendung in größeren Applikationen.
- **Datentyp-Konvertierung**: Die Umwandlung von `DWORD` (32-Bit, vorzeichenlos) in `UINT` (16-Bit, vorzeichenlos) kann je nach Wertbereich zu Informationsverlust führen (z. B. wenn der DWORD-Wert größer als 65535 ist). Der Anwender ist für die Wertebereichsüberwachung verantwortlich.
- **Unidirektionale Schnittstelle**: Sowohl der Eingangs- als auch der Ausgangs-Adapter sind unidirektional ausgelegt (nur eine Ereignis-/Datenrichtung).
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) verfügbar.

## Zustandsübersicht
Der `AD_TO_AUI`-Baustein besitzt keinen eigenen internen Zustand. Das Verhalten ist rein kombinatorisch in Verbindung mit der ereignisgesteuerten Ausführung des enthaltenen Konvertierungsbausteins. Es gibt keine Initialisierungs- oder Fehlerzustände; die Konvertierung erfolgt bei jedem eingehenden Ereignis sofort.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Wenn ein vorhandener Funktionsblock oder ein Subsystem nur einen AUI-Adapter (UINT) unterstützt, aber die Datenquelle einen AD-Adapter (DWORD) liefert.
- **Datenreduktion**: Gezieltes Kürzen eines 32-Bit-Wertes auf 16 Bit für nachgelagerte Verarbeitungslogik.
- **Integration in bestehende Steuerungen**: Austausch von Adaptern zwischen verschiedenen Bussystemen oder Kommunikationsprotokollen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- **AUI_TO_AD**: Führt die umgekehrte Konvertierung (UINT nach DWORD) durch. Beide Bausteine sind symmetrisch aufgebaut und nutzen die entsprechenden Standard-Konvertierungsfunktionen.
- **Direkte Typumwandlung**: Eine manuelle Implementierung mit einem `F_DWORD_TO_UINT`-Baustein und Adaptern wäre möglich, aber der Composite-Baustein bietet eine gekapselte, wiederverwendbare Lösung.

## Fazit
Der `AD_TO_AUI`-Baustein bietet eine einfache und zuverlässige Möglichkeit, zwischen zwei gängigen Adaptertypen zu konvertieren. Er reduziert den Entwicklungsaufwand, indem er die notwendige Verschaltung und Konvertierung kapselt und als wiederverwendbare Komponente bereitstellt. Trotz der potenziellen Wertebereichseinschränkung (DWORD → UINT) ist er ein nützliches Werkzeug für die Integration heterogener Systemteile in der Steuerungstechnik.