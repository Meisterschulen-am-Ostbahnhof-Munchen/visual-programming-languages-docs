# AUDI_SPLIT_6


![AUDI_SPLIT_6](./AUDI_SPLIT_6.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_SPLIT_6** dient als generischer Verteiler (Splitter) für einen unidirektionalen AUDI-Adapter. Er empfängt einen eingehenden Adapter-Datenstrom über einen Socket und leitet diesen unverändert an sechs separate Ausgangsadapter (Plugs) weiter. Der Baustein ist generisch ausgelegt, sodass der konkrete Adaptertyp über das Attribut `GenericClassName` konfiguriert werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket   | **IN**  | `adapter::types::unidirectional::AUDI` | Eingehender Adapter für den zu verteilenden Datenstrom. |
| Plug     | **OUT1** | `adapter::types::unidirectional::AUDI` | Erster Ausgangsadapter (Kopie des Eingangs). |
| Plug     | **OUT2** | `adapter::types::unidirectional::AUDI` | Zweiter Ausgangsadapter. |
| Plug     | **OUT3** | `adapter::types::unidirectional::AUDI` | Dritter Ausgangsadapter. |
| Plug     | **OUT4** | `adapter::types::unidirectional::AUDI` | Vierter Ausgangsadapter. |
| Plug     | **OUT5** | `adapter::types::unidirectional::AUDI` | Fünfter Ausgangsadapter. |
| Plug     | **OUT6** | `adapter::types::unidirectional::AUDI` | Sechster Ausgangsadapter. |

## Funktionsweise

Der Baustein agiert als reiner Verteiler ohne Datenverarbeitung. Der über den Socket **IN** eintreffende Datenstrom wird unverändert und parallel an alle sechs Ausgangsadapter (OUT1–OUT6) weitergeleitet. Die Verteilung erfolgt kontinuierlich, sobald der Eingangsadapter Daten bereitstellt. Da der Baustein generisch ist, kann er durch Setzen des Attributs `eclipse4diac::core::GenericClassName` auf einen spezifischen Adaptertyp (z. B. einen eigenen abgeleiteten Typ) angepasst werden.

## Technische Besonderheiten

- **Generische Auslegung:** Der FB nutzt die 4diac-Generik-Mechanismen (`GenericClassName`). Dadurch kann der Adaptertyp zur Laufzeit oder bei der Instanziierung festgelegt werden, ohne den Baustein neu zu kompilieren.
- **Unidirektional:** Sowohl der Eingangs- als auch die Ausgangsadapter sind unidirektional. Eine Rückmeldung von den Ausgängen zum Eingang ist nicht vorgesehen.
- **Keine Ereignissteuerung:** Der Baustein besitzt kein Ereignis-Interface und kein ECC. Die Datenweitergabe erfolgt rein datengetrieben (sobald am IN-Socket Daten anliegen).
- **Kein interner Zustand:** Es findet keine Zustandsänderung statt; der FB ist stateless.

## Zustandsübersicht

Es existiert kein Zustandsautomat (ECC). Der Baustein führt keine sequenziellen Abläufe aus.

## Anwendungsszenarien

- **Datenverteilung:** Ein von einer Sensorik oder einem anderen FB bereitgestellter AUDI-Datenstrom soll an mehrere nachfolgende Komponenten gleichzeitig gesendet werden, z. B. an eine Visualisierung, eine Logging-Komponente und eine Steuerungslogik.
- **Parallele Verarbeitung:** Wenn derselbe Datenstrom in unterschiedlichen Pfadabschnitten parallel weiterverarbeitet werden muss, z. B. Filterung, Aufbereitung, Speicherung.
- **Generischer Einsatz:** Durch die konfigurierbare Typzuweisung kann der FB in verschiedenen Projekten mit unterschiedlichen Adapterdefinitionen eingesetzt werden, ohne die Quellbasis anpassen zu müssen.

## Vergleich mit ähnlichen Bausteinen

Es existieren andere Split-Bausteine (z. B. `AUDI_SPLIT_2`, `AUDI_SPLIT_4`), die sich lediglich in der Anzahl der Ausgänge unterscheiden. Der `AUDI_SPLIT_6` bietet mit sechs Ausgängen eine höhere Verteilungsdichte. Im Gegensatz zu reinen Daten-Splittern für Basisdatentypen arbeitet dieser FB ausschließlich mit AUDI-Adaptern und berücksichtigt die unidirektionale Kopplung.

## Fazit

Der `AUDI_SPLIT_6` ist ein einfacher, aber flexibler Baustein zur Vervielfachung von Adapterverbindungen in einer 4diac-Umgebung. Seine generische Natur und die schlanke Implementierung ohne Ereignis-Overhead machen ihn ideal für Szenarien, in denen ein eingehender Datenstrom an mehrere unabhängige Empfänger verteilt werden muss.