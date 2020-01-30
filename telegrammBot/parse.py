import requests

req = requests.get("https://progbase.herokuapp.com/api/v1")
print(req.content)
with open("2.json", "w") as f:
    f.write(str(req.content))


