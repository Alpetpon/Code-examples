import json
from ipaddress import IPv4Interface
from datetime import datetime, timedelta, timezone

class MalwareIncidentCardEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, MalwareIncidentCard):
            infection_chain_dict = {}
            for index, event in enumerate(obj.get_infection_chain()):
                device_info = {
                    "malware_name": event.malware_name,
                    "infected_time": event.infected_time.isoformat(),
                    "device_hostname": event.device.hostname,
                    "device_ip_interface": str(event.device.ip_interface)
                }
                infection_chain_dict[str(index)] = device_info

            return {
                "common": obj.common_info,
                "creation_time": obj.creation_time.isoformat(),
                "infection_chain": infection_chain_dict
            }
        return super().default(obj)


class Device:
    hostname: str
    ip_interface: IPv4Interface


class InfectedEvent:
    def __init__(self):
        self.__infected_time = datetime.now(timezone.utc)

    @property
    def infected_time(self):
        return self.__infected_time

    @infected_time.setter
    def infected_time(self, value):
        self.__infected_time = value

    device: Device
    malware_name: str


class MalwareIncidentCard:
    creation_time: datetime
    __infection_chain: list[InfectedEvent]
    common_info: str

    def __init__(self):
        self.__infection_chain = list()

    def add_infected_event(self, infected_event: InfectedEvent):
        self.__infection_chain.append(infected_event)

    def get_infection_chain(self):
        return list(self.__infection_chain)


def create_test_incident_card():
    now = datetime.now(timezone.utc)
    malware_name = 'cool malware name'

    inc = MalwareIncidentCard()
    inc.creation_time = now + timedelta(minutes=2)
    inc.common_info = 'common info of testing incident'

    dev1 = Device()
    dev1.ip_interface = IPv4Interface('10.10.100.52/25')
    dev1.hostname = 'cent-web-01p'

    ie1 = InfectedEvent()
    ie1.device = dev1
    ie1.infected_time = now
    ie1.malware_name = malware_name

    dev2 = Device()
    dev2.ip_interface = IPv4Interface('10.10.100.53/25')
    dev2.hostname = 'cent-web-02p'

    ie2 = InfectedEvent()
    ie2.device = dev2
    ie2.infected_time = now + timedelta(minutes=6)
    ie2.malware_name = malware_name

    inc.add_infected_event(ie1)
    inc.add_infected_event(ie2)
    return inc



incident_card = create_test_incident_card()
encoded_json = json.dumps(incident_card, cls=MalwareIncidentCardEncoder, indent=4)
print(encoded_json)

decoded_dict = json.loads(encoded_json)
new_incident_card = MalwareIncidentCard()
new_incident_card.creation_time = datetime.fromisoformat(decoded_dict['creation_time'])
new_incident_card.common_info = decoded_dict['common']
for index, event_data in decoded_dict['infection_chain'].items():
    device = Device()
    device.hostname = event_data['device_hostname']
    device.ip_interface = IPv4Interface(event_data['device_ip_interface'])
    infected_event = InfectedEvent()
    infected_event.device = device
    infected_event.infected_time = datetime.fromisoformat(event_data['infected_time'])
    infected_event.malware_name = event_data['malware_name']
    new_incident_card.add_infected_event(infected_event)


print("\nDecoded and reconstructed MalwareIncidentCard object:")
print("Common info:", new_incident_card.common_info)
print("Creation time:", new_incident_card.creation_time)
print("Infection chain:")
for index, event in enumerate(new_incident_card.get_infection_chain()):
    print(f"Event {index + 1}:")
    print("  Malware name:", event.malware_name)
    print("  Infected time:", event.infected_time)
    print("  Device hostname:", event.device.hostname)
    print("  Device IP interface:", event.device.ip_interface)
